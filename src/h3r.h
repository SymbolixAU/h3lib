

// #include <R.h>
#include <stdint.h>     // uint64_t
#include <Rinternals.h>

#ifndef R_H3R_H
#define R_H3R_H


// h3api.h     -> h3r.h          ->  h3rapi.h ( C || C++)
// latLngToCel -> h3LatLngToCell ->  h3r_latLngToCell || h3r::latLngToCell

SEXP h3LatLngToCell(SEXP lat, SEXP lon, SEXP res);
SEXP h3CellToLatLng(SEXP h3);
SEXP h3CellToBoundary(SEXP h3);

// SEXP h3StringToH3(SEXP h);
// SEXP h3H3ToString(SEXP h);

// SEXP h3DirectionForNeighbor(SEXP origin, SEXP destination);

#endif
