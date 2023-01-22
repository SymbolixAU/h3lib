
#include "h3lib.h"

//#include <R.h>
//#include <Rinternals.h>
//#include <stdlib.h> // for NULL
#include <Rconfig.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>


// SEXP h3lib_latLngToCell(SEXP lat, SEXP lon, SEXP res);

/* Define .Call functions */
static const R_CallMethodDef callMethods[] = {
  {"h3libLatLngToCell",   (DL_FUNC) &h3LatLngToCell,   3},
  {"h3libCellToLatLng",   (DL_FUNC) &h3CellToLatLng,   1},
  {NULL,                   NULL,                            0}
};


void attribute_visible R_init_h3lib(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);

  R_RegisterCCallable("h3lib", "h3lib_latLngToCell", (DL_FUNC) &h3LatLngToCell);
  R_RegisterCCallable("h3lib", "h3lib_cellToLatLng", (DL_FUNC) &h3CellToLatLng);

  R_forceSymbols(info, TRUE);  // controls visibility
}

// void R_unload_h3lib(DllInfo *info)
// {
//   // TODO:
//   /* Release Resources */
// }
