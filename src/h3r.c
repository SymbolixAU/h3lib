
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3api.h"
#include "algos.h"

SEXP h3StringToH3(SEXP h) {
  R_xlen_t n = Rf_xlength(h);

  SEXP h3 = PROTECT(Rf_allocVector(REALSXP, n));
  H3Index* h3Index = (H3Index*) REAL(h3);

  R_xlen_t i;
  // SEXP h3;
  for( i = 0; i < n; i++ ) {
    stringToH3(CHAR(STRING_ELT(h, i)), &h3Index[i]);
  }

  UNPROTECT(1);
  return h3;
}

SEXP h3H3ToString(SEXP h) {

  R_xlen_t n = Rf_xlength(h);
  H3Index* h3 = (H3Index*) REAL(h);

  SEXP result = PROTECT(Rf_allocVector(STRSXP, n));

  char str[17];

  R_xlen_t i;
  for( i = 0; i < n; i++ ) {
    h3ToString(h3[i], str, sizeof(str));
    SET_STRING_ELT(result, i, Rf_mkChar(str));
  }

  UNPROTECT(1);
  return result;
}

SEXP h3DirectionForNeighbor(SEXP origin, SEXP destination) {

    // TODO:
    // origin && destination to H3Index;
    // call directionForNeighbor
    // convert direction to SEXP
    // return
    R_xlen_t n = Rf_xlength(origin);
    H3Index* h3Origin = (H3Index*) REAL(origin);
    H3Index* h3Destination = (H3Index*) REAL(destination);

    SEXP result = PROTECT(Rf_allocVector(INTSXP, n));

    R_xlen_t i;
    for( i = 0; i < n; i++ ) {
      Direction d = directionForNeighbor(h3Origin[i], h3Destination[i]);
      SET_INTEGER_ELT(result, i, d);
    }

    UNPROTECT(1);
    return result;

}

SEXP h3LatLngToCell(SEXP lat, SEXP lon, SEXP res) {

  R_xlen_t n = Rf_xlength(lat);
  R_xlen_t i;
  SEXP cells = PROTECT(Rf_allocVector(STRSXP, n));

  LatLng latLng;
  H3Index h3Index;
  int ires = INTEGER(res)[0];
  char str[17];

  for( i = 0; i < n; i++ ) {

    latLng.lat = degsToRads(REAL(lat)[i]);
    latLng.lng = degsToRads(REAL(lon)[i]);

    latLngToCell(&latLng, ires, &h3Index);
    h3ToString(h3Index, str, 17);

    SET_STRING_ELT(cells, i, Rf_mkChar(str));
  }

  UNPROTECT(1);
  return cells;
}

SEXP h3CellToLatLng(SEXP h3) {

  R_xlen_t n = Rf_length(h3);
  R_xlen_t i;

  H3Index index;
  LatLng ll;

  SEXP lats = PROTECT(Rf_allocVector(REALSXP, n));
  SEXP lons = PROTECT(Rf_allocVector(REALSXP, n));

  for( i = 0; i < n; i++ ) {

    stringToH3(CHAR(STRING_ELT(h3, i)), &index);
    cellToLatLng(index, &ll);

    double lat = radsToDegs(ll.lat);
    double lon = radsToDegs(ll.lng);

    SET_REAL_ELT(lats, i, lat);
    SET_REAL_ELT(lons, i, lon);
  }

  const char *names[] = {"lat","lng",""};
  SEXP res = PROTECT(mkNamed(VECSXP, names));

  SET_VECTOR_ELT(res, 0, lats);
  SET_VECTOR_ELT(res, 1, lons);
  UNPROTECT(3);

  return res;
}
