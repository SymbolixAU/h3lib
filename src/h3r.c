
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3api.h"

SEXP h3LatLngToCell(SEXP lat, SEXP lon, SEXP res) {

  R_xlen_t n = Rf_length(lat);
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
