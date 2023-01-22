
#include "h3lib.h"

//#include <R.h>
//#include <Rinternals.h>
//#include <stdlib.h> // for NULL
#include <Rconfig.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>


SEXP h3lib_latLngToCell(SEXP lat, SEXP lon, SEXP res);

/* Define .Call functions */
static const R_CallMethodDef callMethods[] = {
  {"h3lib_latLngToCell",   (DL_FUNC) &h3lib_latLngToCell,   3},
  {NULL,                   NULL,                            0}
};


void attribute_visible R_init_h3lib(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);

  R_RegisterCCallable("h3lib", "h3lib_latLngToCell", (DL_FUNC) &h3lib_latLngToCell);

  R_forceSymbols(info, TRUE);  // controls visibility
}

void R_unload_h3lib(DllInfo *info)
{
  // TODO:
  /* Release Resources */
}
