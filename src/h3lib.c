
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>

#include "h3api.h"

SEXP CLatLngToCell(SEXP lat, SEXP lon, SEXP res) {
  LatLng latLng;
  //H3Index out;

  // TODO:
  // this is where we'll call the H3 latLngToCell();


  SEXP out = PROTECT(Rf_allocVector(INTSXP, (1)));
  return out;
}

