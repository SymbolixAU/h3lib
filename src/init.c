#include "h3lib.h"

//#include <R.h>
//#include <Rinternals.h>
//#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>


static const R_CallMethodDef callMethods[] = {
{"CLatLngToCell", (DL_FUNC) &CLatLngToCell, 3},
{NULL, NULL, 0}
};


void R_init_h3lib(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);

  R_RegisterCCallable("h3lib", "CLatLngToCell", (DL_FUNC) &CLatLngToCell);

  // R_forceSymbols(info, TRUE);
}

