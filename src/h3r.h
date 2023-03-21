

// #include <R.h>
#include <stdint.h>     // uint64_t
#include <Rinternals.h>

#ifndef R_H3R_H
#define R_H3R_H


// h3api.h     -> h3r.h          ->  h3rapi.h ( C || C++)
// latLngToCel -> h3LatLngToCell ->  h3rLatLngToCell || h3r::latLngToCell

// Indexing
SEXP h3rLatLngToCell(SEXP lat, SEXP lon, SEXP res);
SEXP h3rCellToLatLng(SEXP h3);
SEXP h3rCellToBoundary(SEXP h3);


// Inspection
SEXP h3rGetResolution(SEXP h3);
SEXP h3rGetBaseCellNumber(SEXP h3);
SEXP h3rIsValidCell(SEXP h3);
SEXP h3rIsResClassIII(SEXP h3);
SEXP h3rIsPentagon(SEXP h3);

// Traversal

// Hierarchy
SEXP h3rCellToParent(SEXP h3, SEXP parentResolution);
SEXP h3rCellToChildren(SEXP h3, SEXP childResolution);
// SEXP h3rCellToChildrenSize(SEXP h3, SEXP childResolution);

// Miscellaneous
SEXP h3rGreatCircleDistance(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons, int distType);
SEXP h3rGreatCircleDistanceRads(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons);
SEXP h3rGreatCircleDistanceM(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons);
SEXP h3rGreatCircleDistanceKm(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons);  // returns int64_t


// typedef enum {
//   RADIANS = 0,
//   METERS = 1,
//   KILOMETERS = 2,
// } DistType;



//SEXP h3gridDiskUnsafe(SEXP origins, SEXP k);

// Needs Int64
// SEXP h3maxGridDiskSize(SEXP k);

// SEXP h3StringToH3(SEXP h);
// SEXP h3H3ToString(SEXP h);

// SEXP h3DirectionForNeighbor(SEXP origin, SEXP destination);

#endif
