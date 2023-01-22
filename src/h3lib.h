

// #include <R.h>
#include <Rinternals.h>

#ifndef R_H3LIB_H
#define R_H3LIB_H


// h3api.h     -> h3lib.h        ->  h3libapi.h ( C || C++)
// latLngToCel -> h3LatLngToCell ->  h3lib_latLngToCell || h3lib::latLngToCell

SEXP h3LatLngToCell(SEXP lat, SEXP lon, SEXP res);
SEXP h3CellToLatLng(SEXP h3);

#endif
