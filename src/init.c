
#include "h3lib.h"

#include <Rdefines.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

/*
static const
R_CallMethodDef callMethods[] = {
{"CLatLngToCell", (DL_FUNC) &h3libLatLngToCell, -1},
{NULL, NULL, 0}
};
*/

void attribute_visible R_init_h3lib(DllInfo *info)
{
  R_RegisterCCallable("h3lib", "CLatLngToCell", (DL_FUNC) &CLatLngToCell);
}

