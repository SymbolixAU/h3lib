
#include "h3rc.h"

#include <Rconfig.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* Function Definitions for {h3rc} */
static const R_CallMethodDef callMethods[] = {
  {"h3rcLatLngToCell",    (DL_FUNC) &h3rcLatLngToCell,  3},
  {NULL, NULL, 0}
};

/* Imports from h3lib */
SEXP (*h3rLatLngToCell)(SEXP,SEXP,SEXP);

void R_init_h3rc(DllInfo *info)

{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);
  R_useDynamicSymbols(info, FALSE);

  /* Imports from h3lib */
  h3rLatLngToCell = (SEXP(*)(SEXP,SEXP,SEXP)) R_GetCCallable("h3r", "h3rLatLngToCell");
}
