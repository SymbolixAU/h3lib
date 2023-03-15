
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
  {"h3rLatLngToCell",   (DL_FUNC) &h3LatLngToCell,   3},
  {"h3rCellToLatLng",   (DL_FUNC) &h3CellToLatLng,   1},
  {"h3rCellToBoundary", (DL_FUNC) &h3CellToBoundary, 1},
  // {"h3rH3ToString",     (DL_FUNC) &h3H3ToString,     1},
  // {"h3rStringToH3",     (DL_FUNC) &h3StringToH3,     1},
  // {"h3rDirectionForNeighbor", (DL_FUNC) &h3DirectionForNeighbor, 2},
  {"h3rGreatCircleDistanceRads", (DL_FUNC) &h3GreatCircleDistanceRads, 4},
  {"h3rGreatCircleDistanceM", (DL_FUNC) &h3GreatCircleDistanceM, 4},
  {"h3rGreatCircleDistanceKm", (DL_FUNC) &h3GreatCircleDistanceKm, 4},
  {NULL,                NULL,                        0}
};


void attribute_visible R_init_h3r(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);

  R_RegisterCCallable("h3r", "h3LatLngToCell",    (DL_FUNC) &h3LatLngToCell);
  R_RegisterCCallable("h3r", "h3r_cellToLatLng",    (DL_FUNC) &h3CellToLatLng);
  R_RegisterCCallable("h3r", "h3r_cellToBoundary",  (DL_FUNC) &h3CellToBoundary);
  // R_RegisterCCallable("h3r", "h3r_h3ToString",   (DL_FUNC) &h3H3ToString);
  // R_RegisterCCallable("h3r", "h3r_stringToH3",   (DL_FUNC) &h3StringToH3);
  // R_RegisterCCallable("h3r", "h3r_directionForNeighbor", (DL_FUNC) &h3DirectionForNeighbor);
  R_RegisterCCallable("h3r", "h3r_greatCircleDistanceRads", (DL_FUNC) &h3GreatCircleDistanceRads);
  R_RegisterCCallable("h3r", "h3r_greatCircleDistanceM", (DL_FUNC) &h3GreatCircleDistanceM);
  R_RegisterCCallable("h3r", "h3r_greatCircleDistanceKm", (DL_FUNC) &h3GreatCircleDistanceKm);

  R_forceSymbols(info, TRUE);  // controls visibility


}

void R_unload_h3r(DllInfo *info)
{
  // TODO:
  /* Release Resources */
}
