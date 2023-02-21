
#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include "h3rapi.h"

SEXP h3rcLatLngToCell(SEXP lat, SEXP lon, SEXP res) {
  return h3r_latLngToCell(lat, lon, res);
}
