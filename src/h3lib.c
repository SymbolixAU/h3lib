
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3api.h"

SEXP h3lib_latLngToCell(SEXP lat, SEXP lon, SEXP res) {
  LatLng latLng;
  H3Index h3Index;
  int ires = INTEGER(res)[0];

  // TODO:
  // this is where we'll call the H3 latLngToCell();
  latLng.lat = degsToRads(REAL(lat)[0]);
  latLng.lng = degsToRads(REAL(lon)[0]);

  latLngToCell(&latLng, ires, &h3Index);

  char str[17];
  h3ToString(h3Index, str, 17);

  SEXP out = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(out, 0, Rf_mkChar(str));
  UNPROTECT(1);

  return out;
}

