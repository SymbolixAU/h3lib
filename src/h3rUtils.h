
#include "h3api.h"
#include <Rinternals.h>


#ifndef R_H3R_UTILS
#define R_H3R_UTILS

//' Fill Lat Lng
//'
//' fills the `latLng` object with the contents of SEXP lat/lon vectors
void sexpToLatLng(LatLng *latLng, SEXP lat, SEXP lon, R_xlen_t idx);

//' SEXP String to H3
//'
//' Converts an R String (SEXP) to an `H3Index`
H3Index sexpStringToH3(SEXP h3, R_xlen_t idx);

//' LatLng to SEXP
//'
//' Fills vectos of SEXP lat/lon objects with the contents of a LatLng
void latLngToSexp(LatLng *latLng, SEXP lats, SEXP lons, R_xlen_t idx);

//' LatLngList
//'
//' Creates a list of lat/lon elements
SEXP latLngList(SEXP lats, SEXP lons);

//' CellBoundaryToList
//'
//' Creates a list of lon/lats from a CellBoundary
SEXP cellBoundaryToList(CellBoundary *cb);




#endif
