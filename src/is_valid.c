
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3Index.h"
#include <inttypes.h>

SEXP is_valid(SEXP cell) {
  H3Index h3;

  SEXP cellString = STRING_ELT(cell, 0);
  const char* h3String = CHAR(cellString);

  stringToH3(h3String, &h3);

  int valid = isValidCell(h3);

  SEXP out = PROTECT(Rf_allocVector(INTSXP, 1));

  UNPROTECT(1);
  return out;
}
