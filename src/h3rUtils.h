
#include "h3api.h"
#include <Rinternals.h>


#ifndef R_H3R_UTILS
#define R_H3R_UTILS

//' Fill Lat Lng
//'
//' fills the `latLng` object with the contents of SEXP lat/lon vectors
void sexpToLatLng(LatLng *latLng, SEXP lat, SEXP lon, R_xlen_t idx);

//' H3 To Sexp String
//'
//' converts an h3 index to a SEXP string (`Rf_mkChar()`)
SEXP h3ToSexpString(H3Index h3);

//' H3 Vec To Sexp String
//'
//' Converts an array of H3 indexes to a SEXP (STRSXP) vector
SEXP h3VecToSexpString(H3Index *h3, R_xlen_t n);

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
