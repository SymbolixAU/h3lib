

// #include <R.h>
#include <Rinternals.h>

#ifndef R_H3LIB_H
#define R_H3LIB_H

SEXP h3LatLngToCell(SEXP lat, SEXP lon, SEXP res);
SEXP h3CellToLatLng(SEXP h3);

#endif
