

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
SEXP h3rGetIcosahedronFaces(SEXP h3);
SEXP h3rMaxFaceCount(SEXP h3);

// Traversal
SEXP h3rGridDisk(SEXP h3, SEXP k);
SEXP h3rMaxGridDiskSize(SEXP k);
SEXP h3rGridDiskDistances(SEXP h3, SEXP k);
SEXP h3rGridDiskUnsafe(SEXP h3, SEXP k) ;
SEXP h3rGridDiskDistancesUnsafe(SEXP h3, SEXP k) ;
SEXP h3rGridDiskDistancesSafe(SEXP h3, SEXP k);
SEXP h3rGridRingUnsafe(SEXP h3, SEXP k);
SEXP h3rGridPathCells(SEXP origH3, SEXP destH3);
SEXP h3rGridPathCellsSize(SEXP origH3, SEXP destH3);
SEXP h3rGridDistance(SEXP origH3, SEXP destH3);

// Hierarchy
SEXP h3rCellToParent(SEXP h3, SEXP parentResolution);
SEXP h3rCellToChildren(SEXP h3, SEXP childResolution);
// SEXP h3rCellToChildrenSize(SEXP h3, SEXP childResolution);

// Regions

// Directed Edges
SEXP h3rAreNeighborCells(SEXP origH3, SEXP destH3); 
SEXP h3rCellsToDirectedEdge(SEXP origH3, SEXP destH3);
SEXP h3rIsValidDirectedEdge(SEXP edge);
SEXP h3rGetDirectedEdgeOrigin(SEXP edge);
SEXP h3rGetDirectedEdgeDestination(SEXP edge);
SEXP h3rDirectedEdgeToCells(SEXP edge);
SEXP h3rOriginToDirectedEdges(SEXP origH3);

// Vertexes
SEXP h3rCellToVertex(SEXP h3, SEXP vertexNum);
SEXP h3rCellToVertexes(SEXP h3);
SEXP h3rVertexToLatLng(SEXP h3);
SEXP h3rIsValidVertex(SEXP h3);

// Miscellaneous
SEXP h3rDegsToRads(SEXP degrees);
SEXP h3rRadsToDegs(SEXP degrees);

SEXP h3rGetHexagonArea(SEXP res, int areaType);
SEXP h3rGetHexagonAreaAvgM2(SEXP res);
SEXP h3rGetHexagonAreaAvgKm2(SEXP res);

SEXP h3rCellArea(SEXP h3, int areaType);
SEXP h3rCellAreaRads2(SEXP h3);
SEXP h3rCellAreaM2(SEXP h3);
SEXP h3rCellAreaKm2(SEXP h3);

SEXP h3rGetHexagonEdgeLengthAvg(SEXP res, int distType);
SEXP h3rGetHexagonEdgeLengthAvgM(SEXP res);
SEXP h3rGetHexagonEdgeLengthAvgKm(SEXP res);

SEXP h3rEdgeLength(SEXP edge, int distType);
SEXP h3rEdgeLengthRads(SEXP edge);
SEXP h3rEdgeLengthM(SEXP edge);
SEXP h3rEdgeLengthKm(SEXP edge);

SEXP h3rGetNumCells(SEXP res);
SEXP h3rGetRes0Cells();
SEXP h3rRes0CellCount();

SEXP h3rGetPentagons(SEXP res);
SEXP h3rPentagonCount();

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
