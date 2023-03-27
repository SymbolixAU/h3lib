
#include "h3api.h"

#include "algos.h" // directionForNeighbor

#include <R.h>
#include <Rconfig.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>


/* Define .Call functions */
static const R_CallMethodDef callMethods[] = {
  {NULL,                NULL,                        0}
};

void attribute_visible R_init_h3lib(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);

  // Indexing
  R_RegisterCCallable("h3lib", "latLngToCell",         (DL_FUNC) &latLngToCell);
  R_RegisterCCallable("h3lib", "cellToLatLng",         (DL_FUNC) &cellToLatLng);
  R_RegisterCCallable("h3lib", "cellToBoundary",       (DL_FUNC) &cellToBoundary);

  // Inspection
  R_RegisterCCallable("h3lib", "stringToH3",           (DL_FUNC) &stringToH3); // H3 Internal
  R_RegisterCCallable("h3lib", "h3ToString",           (DL_FUNC) &h3ToString);

  // Traversal
  R_RegisterCCallable("h3lib", "gridPathCellsSize",    (DL_FUNC) &gridPathCellsSize);
  R_RegisterCCallable("h3lib", "gridPathCells",        (DL_FUNC) &gridPathCells);

  // Hierarchy


  // Regions


  // Directed Edges


  // Vertexes


  // Miscellaneous
  R_RegisterCCallable("h3lib", "degsToRads",           (DL_FUNC) &degsToRads);
  R_RegisterCCallable("h3lib", "radsToDegs",           (DL_FUNC) &radsToDegs);

  // Non-API
  R_RegisterCCallable("h3lib", "directionForNeighbor", (DL_FUNC) &directionForNeighbor);


  R_forceSymbols(info, TRUE);  // controls visibility


}

void R_unload_h3lib(DllInfo *info)
{
  // TODO:
  /* Release Resources */
}
