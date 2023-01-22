
#include "h3r.h"

#include <R.h>
// #include <Rinternals.h>
//#include <stdlib.h> // for NULL
#include <Rconfig.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>


// uint64_t H3Index;

/* Define .Call functions */
static const R_CallMethodDef callMethods[] = {
  {"h3rLatLngToCell",   (DL_FUNC) &h3LatLngToCell,   3},
  {"h3rCellToLatLng",   (DL_FUNC) &h3CellToLatLng,   1},
  {NULL,                   NULL,                            0}
};


void attribute_visible R_init_h3r(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);

  R_RegisterCCallable("h3r", "h3r_latLngToCell", (DL_FUNC) &h3LatLngToCell);
  R_RegisterCCallable("h3r", "h3r_cellToLatLng", (DL_FUNC) &h3CellToLatLng);

  R_forceSymbols(info, TRUE);  // controls visibility
}

void R_unload_h3r(DllInfo *info)
{
  // TODO:
  /* Release Resources */
}
