

// #include <R.h>
#include <Rinternals.h>

#ifndef R_H3R_H
#define R_H3R_H


// h3api.h     -> h3r.h          ->  h3rapi.h ( C || C++)
// latLngToCel -> h3LatLngToCell ->  h3r_latLngToCell || h3r::latLngToCell


SEXP h3LatLngToCell(SEXP lat, SEXP lon, SEXP res);
SEXP h3CellToLatLng(SEXP h3);

#endif
