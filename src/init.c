
#include "h3r.h"

#include <R.h>
// #include <Rinternals.h>
//#include <stdlib.h> // for NULL
#include <Rconfig.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

// #include "coordijk.h"

// uint64_t H3Index;

/* Define .Call functions */
static const R_CallMethodDef callMethods[] = {

  // Indexing
  {"h3rLatLngToCell",   (DL_FUNC) &h3rLatLngToCell,   3},
  {"h3rCellToLatLng",   (DL_FUNC) &h3rCellToLatLng,   1},
  {"h3rCellToBoundary", (DL_FUNC) &h3rCellToBoundary, 1},

  // Inspection
  {"h3rGetResolution",     (DL_FUNC) &h3rGetResolution,     1},
  {"h3rGetBaseCellNumber", (DL_FUNC) &h3rGetBaseCellNumber, 1},
  {"h3rIsValidCell",       (DL_FUNC) &h3rIsValidCell,       1},
  {"h3rIsResClassIII",     (DL_FUNC) &h3rIsResClassIII,     1},
  {"h3rIsPentagon",        (DL_FUNC) &h3rIsPentagon,        1},

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


  // Miscellaneous
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
  R_RegisterCCallable("h3r", "h3rLatLngToCell",    (DL_FUNC) &h3rLatLngToCell);
  R_RegisterCCallable("h3r", "h3rCellToLatLng",    (DL_FUNC) &h3rCellToLatLng);
  R_RegisterCCallable("h3r", "h3rCellToBoundary",  (DL_FUNC) &h3rCellToBoundary);

  // Inspection
  R_RegisterCCallable("h3r", "h3rGetResolution",     (DL_FUNC) &h3rGetResolution);
  R_RegisterCCallable("h3r", "h3rGetBaseCellNumber", (DL_FUNC) &h3rGetBaseCellNumber);
  R_RegisterCCallable("h3r", "h3rIsValidCell",       (DL_FUNC) &h3rIsValidCell);
  R_RegisterCCallable("h3r", "h3rIsResClassIII",     (DL_FUNC) &h3rIsResClassIII);
  R_RegisterCCallable("h3r", "h3rIsPentagon",        (DL_FUNC) &h3rIsPentagon);

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


  // Miscellaneous
  R_RegisterCCallable("h3r", "h3rGreatCircleDistanceRads", (DL_FUNC) &h3rGreatCircleDistanceRads);
  R_RegisterCCallable("h3r", "h3rGreatCircleDistanceM",    (DL_FUNC) &h3rGreatCircleDistanceM);
  R_RegisterCCallable("h3r", "h3rGreatCircleDistanceKm",   (DL_FUNC) &h3rGreatCircleDistanceKm);

  R_forceSymbols(info, TRUE);  // controls visibility


}

void R_unload_h3r(DllInfo *info)
{
  // TODO:
  /* Release Resources */
}
