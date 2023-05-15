
# h3lib

## What is `h3lib`?

`h3lib` is an R pacakge. But it’s also **not** an R package.

There aren’t any R functions you can call, nor can you import this
pacakge as-is into your own.

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

but it also defines which Routines it wants to **import**

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
