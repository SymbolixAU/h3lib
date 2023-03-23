
#include "h3r.h"
#include "h3api.h"

#include "algos.h" // directionForNeighbor

#include <R.h>
// #include <Rinternals.h>
//#include <stdlib.h> // for NULL
#include <Rconfig.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>



/* Define .Call functions */
static const R_CallMethodDef callMethods[] = {

  // Indexing
  {"h3rLatLngToCell",   (DL_FUNC) &h3rLatLngToCell,   3},
  {"h3rCellToLatLng",   (DL_FUNC) &h3rCellToLatLng,   1},
  {"h3rCellToBoundary", (DL_FUNC) &h3rCellToBoundary, 1},

  // Inspection
  {"h3rGetResolution",       (DL_FUNC) &h3rGetResolution,       1},
  {"h3rGetBaseCellNumber",   (DL_FUNC) &h3rGetBaseCellNumber,   1},
  {"h3rIsValidCell",         (DL_FUNC) &h3rIsValidCell,         1},
  {"h3rIsResClassIII",       (DL_FUNC) &h3rIsResClassIII,       1},
  {"h3rIsPentagon",          (DL_FUNC) &h3rIsPentagon,          1},
  {"h3rGetIcosahedronFaces", (DL_FUNC) &h3rGetIcosahedronFaces, 1},
  {"h3rMaxFaceCount",        (DL_FUNC) &h3rMaxFaceCount,        1},

  // Traversal

  // Hierarchy
  {"h3rCellToParent",        (DL_FUNC) &h3rCellToParent,       2},
  {"h3rCellToChildren",      (DL_FUNC) &h3rCellToChildren,     2},
  // {"h3rCellToChildrenSize",  (DL_FUNC) &h3rCellToChildrenSize, 2},

  // {"h3rH3ToString",     (DL_FUNC) &h3H3ToString,     1},
  // {"h3rStringToH3",     (DL_FUNC) &h3StringToH3,     1},
  // {"h3rDirectionForNeighbor", (DL_FUNC) &h3DirectionForNeighbor, 2},

  // Regions


  // Directed Edges


  // Vertexes
  {"h3rCellToVertex",      (DL_FUNC) &h3rCellToVertex,   1},
  {"h3rCellToVertexes",    (DL_FUNC) &h3rCellToVertexes, 1},
  {"h3rVertexToLatLng",    (DL_FUNC) &h3rVertexToLatLng, 1},
  {"h3rIsValidVertex",     (DL_FUNC) &h3rIsValidVertex,  1},


  // Miscellaneous
  {"h3rDegsToRads",              (DL_FUNC) &h3rDegsToRads,              1},     // H3 Internal
  {"h3rRadsToDegs",              (DL_FUNC) &h3rRadsToDegs,              1},


  {"h3rGetHexagonAreaAvgM2",   (DL_FUNC) &h3rGetHexagonAreaAvgM2,    1},
  {"h3rGetHexagonAreaAvgKm2",   (DL_FUNC) &h3rGetHexagonAreaAvgKm2,   1},

  {"h3rCellAreaRads2", (DL_FUNC) &h3rCellAreaRads2, 1},
  {"h3rCellAreaM2",    (DL_FUNC) &h3rCellAreaM2,    1},
  {"h3rCellAreaKm2",   (DL_FUNC) &h3rCellAreaKm2,   1},

  {"h3rGetHexagonEdgeLengthAvgM",    (DL_FUNC) &h3rGetHexagonEdgeLengthAvgM,    1},
  {"h3rGetHexagonEdgeLengthAvgKm",   (DL_FUNC) &h3rGetHexagonEdgeLengthAvgKm,   1},

  {"h3rEdgeLengthRads", (DL_FUNC) &h3rEdgeLengthRads, 1},
  {"h3rEdgeLengthM",    (DL_FUNC) &h3rEdgeLengthM,    1},
  {"h3rEdgeLengthKm",   (DL_FUNC) &h3rEdgeLengthKm,   1},


  {"h3rGetNumCells", (DL_FUNC) &h3rGetNumCells, 1},
  {"h3rGetRes0Cells",    (DL_FUNC) &h3rGetRes0Cells,    0},
  {"h3rRes0CellCount",   (DL_FUNC) &h3rRes0CellCount,   1},

  {"h3rGetPentagons",    (DL_FUNC) &h3rGetPentagons,    1},
  {"h3rPentagonCount",   (DL_FUNC) &h3rPentagonCount,   0},

  {"h3rGreatCircleDistanceRads", (DL_FUNC) &h3rGreatCircleDistanceRads, 4},
  {"h3rGreatCircleDistanceM",    (DL_FUNC) &h3rGreatCircleDistanceM,    4},
  {"h3rGreatCircleDistanceKm",   (DL_FUNC) &h3rGreatCircleDistanceKm,   4},

  {NULL,                NULL,                        0}
};


void attribute_visible R_init_h3r(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);

  // Indexing
  R_RegisterCCallable("h3r", "latLngToCell",       (DL_FUNC) &latLngToCell);       // H3 Internal

  R_RegisterCCallable("h3r", "h3rLatLngToCell",    (DL_FUNC) &h3rLatLngToCell);
  R_RegisterCCallable("h3r", "h3rCellToLatLng",    (DL_FUNC) &h3rCellToLatLng);
  R_RegisterCCallable("h3r", "h3rCellToBoundary",  (DL_FUNC) &h3rCellToBoundary);

  // Inspection
  R_RegisterCCallable("h3r", "h3rGetResolution",       (DL_FUNC) &h3rGetResolution);
  R_RegisterCCallable("h3r", "h3rGetBaseCellNumber",   (DL_FUNC) &h3rGetBaseCellNumber);
  R_RegisterCCallable("h3r", "h3rIsValidCell",         (DL_FUNC) &h3rIsValidCell);
  R_RegisterCCallable("h3r", "h3rIsResClassIII",       (DL_FUNC) &h3rIsResClassIII);
  R_RegisterCCallable("h3r", "h3rIsPentagon",          (DL_FUNC) &h3rIsPentagon);
  R_RegisterCCallable("h3r", "h3rGetIcosahedronFaces", (DL_FUNC) &h3rGetIcosahedronFaces);
  R_RegisterCCallable("h3r", "h3rMaxFaceCount",        (DL_FUNC) &h3rMaxFaceCount);

  // Traversal

  // Hierarchy
  R_RegisterCCallable("h3r", "h3rCellToParent",          (DL_FUNC) &h3rCellToParent);
  R_RegisterCCallable("h3r", "h3rCellToChildren",        (DL_FUNC) &h3rCellToChildren);
  // R_RegisterCCallable("h3r", "h3rCellToChildrenSize",        (DL_FUNC) &h3rCellToChildrenSize);

  // R_RegisterCCallable("h3r", "h3r_h3ToString",   (DL_FUNC) &h3H3ToString);
  // R_RegisterCCallable("h3r", "h3r_stringToH3",   (DL_FUNC) &h3StringToH3);
  // R_RegisterCCallable("h3r", "h3r_directionForNeighbor", (DL_FUNC) &h3DirectionForNeighbor);

  // Regions


  // Directed Edges


  // Vertexes
  R_RegisterCCallable("h3r", "h3rCellToVertex",     (DL_FUNC) &h3rCellToVertex);
  R_RegisterCCallable("h3r", "h3rCellToVertexes",   (DL_FUNC) &h3rCellToVertexes);
  R_RegisterCCallable("h3r", "h3rVertexToLatLng",   (DL_FUNC) &h3rVertexToLatLng);
  R_RegisterCCallable("h3r", "h3rIsValidVertex",    (DL_FUNC) &h3rIsValidVertex);


  // Miscellaneous
  R_RegisterCCallable("h3r", "degsToRads",                 (DL_FUNC) &degsToRads);

  R_RegisterCCallable("h3r", "h3rDegsToRads",              (DL_FUNC) &h3rDegsToRads);
  R_RegisterCCallable("h3r", "h3rRadsToDegs",              (DL_FUNC) &h3rRadsToDegs);

  R_RegisterCCallable("h3r", "h3rGetHexagonAreaAvgM2",    (DL_FUNC) &h3rGetHexagonAreaAvgM2);
  R_RegisterCCallable("h3r", "h3rGetHexagonAreaAvgKm2",   (DL_FUNC) &h3rGetHexagonAreaAvgKm2);

  R_RegisterCCallable("h3r", "h3rCellAreaRads2", (DL_FUNC) &h3rCellAreaRads2);
  R_RegisterCCallable("h3r", "h3rCellAreaM2",    (DL_FUNC) &h3rCellAreaM2);
  R_RegisterCCallable("h3r", "h3rCellAreaKm2",   (DL_FUNC) &h3rCellAreaKm2);

  R_RegisterCCallable("h3r", "h3rGetNumCells",    (DL_FUNC) &h3rGetNumCells);
  R_RegisterCCallable("h3r", "h3rGetRes0Cells",   (DL_FUNC) &h3rGetRes0Cells);
  R_RegisterCCallable("h3r", "h3rRes0CellCount",  (DL_FUNC) &h3rRes0CellCount);

  R_RegisterCCallable("h3r", "h3rGetPentagons",   (DL_FUNC) &h3rGetPentagons);
  R_RegisterCCallable("h3r", "h3rPentagonCount",  (DL_FUNC) &h3rPentagonCount);

  R_RegisterCCallable("h3r", "h3rGreatCircleDistanceRads", (DL_FUNC) &h3rGreatCircleDistanceRads);
  R_RegisterCCallable("h3r", "h3rGreatCircleDistanceM",    (DL_FUNC) &h3rGreatCircleDistanceM);
  R_RegisterCCallable("h3r", "h3rGreatCircleDistanceKm",   (DL_FUNC) &h3rGreatCircleDistanceKm);


  // Non-API
  R_RegisterCCallable("h3r", "directionForNeighbor", (DL_FUNC) &directionForNeighbor);


  R_forceSymbols(info, TRUE);  // controls visibility


}

void R_unload_h3r(DllInfo *info)
{
  // TODO:
  /* Release Resources */
}
