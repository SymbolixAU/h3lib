
# h3lib

## What is `h3lib`?

`h3lib` is an R pacakge. But it’s also **not** an R package.

There aren’t any R functions you can call, nor can you import this
package as-is into your own.

## So, what *is* `h3lib`?

`h3lib` exposes [Uber’s H3](https://h3geo.org/) source files (written in
C) through Callable routines.

It’s these routines that you can then use in your own package.

## How do I call these routines?

Firstly, take a look at `/src/init.c`. You’ll see a whole load of
`R_RegisterCCallable()` calls:

    // Indexing
    R_RegisterCCallable("h3lib", "latLngToCell",         (DL_FUNC) &latLngToCell);
    R_RegisterCCallable("h3lib", "cellToLatLng",         (DL_FUNC) &cellToLatLng);
    R_RegisterCCallable("h3lib", "cellToBoundary",       (DL_FUNC) &cellToBoundary);

These are essentially saying

> Here are some C functions I’d like you to register and make available
> to other packages

Now look in `/inst/include/h3libapi.h`. Here you’ll see all the function
definitions for these registered routines

    // Indexing
    inline H3Error latLngToCell(const LatLng *g, int res, H3Index *out) {
      H3Error(*fun)(const LatLng*, int, H3Index*) =
        (H3Error(*)(const LatLng*, int, H3Index*)) R_GetCCallable("h3lib","latLngToCell");
      return fun(g, res, out);
    }

The registered routines in `init.c` and the definitions in `h3libapi.h`
should match. If there’s something missing, please let us know!

## That explains which routines *can* be called, but you haven’t said *how* to call them?

Yes, I’m getting to that.

To demonstrate how to actually **call** these routines, let’s use the
[h3r](https://github.com/symbolixau/h3r) package as an example.

Here are the steps to call the `latLngToCell` routine defined in `h3lib`

### DESCRIPTION

In the `DESCRIPTION` file you need to link to {h3lib}

    Depends:
      h3lib
    LinkingTo:
      h3lib

### src/init.c

If you look in the `/src/` directory you’ll see various `.c` files.

The `init.c` also contains some `R_RegisterCCallable()` (because it too
is exposing some of its C code to the wider R ecosystem).

But it also defines which Routines it wants to **import**

    H3Error (*latLngToCell);
    H3Error (*cellToLatLng);
    H3Error (*cellToBoundary);
    ... etc

### src/h3rIndexing.c

Then in a .c file, you need to include the `h3libapi.h` file, and that’s
it!

(I’ve highlighted the bit of code that calls the `latLngToCell` routine)


    #include "h3libapi.h"


    SEXP h3rLatLngToCell(SEXP lat, SEXP lon, SEXP res) {

      R_xlen_t n = Rf_xlength(lat);
      R_xlen_t i;
      SEXP cells = PROTECT(Rf_allocVector(STRSXP, n));

      LatLng latLng;
      H3Index h3Index;
      // char str[17];

      for( i = 0; i < n; i++ ) {
        int ires = INTEGER(res)[i];

        sexpToLatLng(&latLng, lat, lon, i);

        h3error(latLngToCell(&latLng, ires, &h3Index), i);   // <-- LOOK HERE; this is calling h3lib latLngToCell
        // h3ToString(h3Index, str, 17);

        SET_STRING_ELT(cells, i, h3ToSexpString(h3Index));
      }

      UNPROTECT(1);
      return cells;
    }

## Working Example

Let’s build our own example that uses `cellToLatLng` to build `{sf}`
polygons.

For this we can link to both `{h3lib}` and `{sfheaders}`

``` r

library(Rcpp)

cppFunction(
  
  depends = c(
    "h3lib"
    , "geometries"  ## <- required because sfheaders depends on it
    , "sfheaders"   ## <- for building sf objects through C++ code
    )
  , includes = c(
    '#include "h3libapi.h"'
    , '#include "sfheaders/sfg/polygon/sfg_polygon.hpp"'
    )
  , code = '
    SEXP cellToPolygon(SEXP h3) {
    
      R_xlen_t n = Rf_xlength(h3);
      R_xlen_t i, j;
      
      Rcpp::List poylgons(n);  // for storing the sfg_polygons
      
      for(i = 0; i < n; ++i) {
        H3Index idx;
        CellBoundary cb;
        
        // convert the SEXP cell (stringVector) to H3Index
        int e1 = stringToH3(CHAR(STRING_ELT(h3, i)), &idx);
        // TODO: handle the error-code `e1`
        
        // Convert H3Index to CellBoundary object
        int e2 = cellToBoundary(idx, &cb);
        // TODO: handle the rror-code `e2`;
        
        // Convert the CellBoundary to sfg_polygon
        // where sfheaders::sfg_polygon accepts a matrix or data-frame
        Rcpp::NumericMatrix latLng(cb.numVerts, 2);
        for(j = 0; j < cb.numVerts; ++j) {
          latLng(j, 0) = radsToDegs(cb.verts[i].lng);
          latLng(j, 1) = radsToDegs(cb.verts[j].lat);
        }
        poylgons[i] = sfheaders::sfg::sfg_polygon(latLng, "XY");
      }
      return poylgons;
    }
  '
)

cellToPolygon(c("8cbe63562a54bff","8cbe635631103ff"))
# [[1]]
# [[1]]
#          [,1]      [,2]
# [1,] 144.9833 -37.82030
# [2,] 144.9833 -37.82019
# [3,] 144.9833 -37.82012
# [4,] 144.9833 -37.82016
# [5,] 144.9833 -37.82026
# [6,] 144.9833 -37.82033
# [7,] 144.9833 -37.82030
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"    
# 
# [[2]]
# [[1]]
#          [,1]      [,2]
# [1,] 144.9675 -37.81851
# [2,] 144.9675 -37.81840
# [3,] 144.9675 -37.81833
# [4,] 144.9675 -37.81837
# [5,] 144.9675 -37.81847
# [6,] 144.9675 -37.81854
# [7,] 144.9675 -37.81851
# 
# attr(,"class")
# [1] "XY"      "POLYGON" "sfg"
```
