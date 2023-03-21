

// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3api.h"
#include "algos.h"

#include "h3rUtils.h"


SEXP h3rGetResolution(SEXP h3) {
  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(INTSXP, n));

  for(i = 0; i < n; i++) {
    H3Index index = sexpStringToH3(h3, i);
    int resolution = getResolution(index);
    SET_INTEGER_ELT(out, i, resolution);
  }

  UNPROTECT(1);
  return out;
}


SEXP h3rGetBaseCellNumber(SEXP h3) {
  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(INTSXP, n));

  for(i = 0; i < n; i++) {
    H3Index index = sexpStringToH3(h3, i);
    int baseNumber = getBaseCellNumber(index);
    SET_INTEGER_ELT(out, i, baseNumber);
  }

  UNPROTECT(1);
  return out;
}


SEXP h3rIsValidCell(SEXP h3) {
  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(INTSXP, n));

  for(i = 0; i < n; i++) {
    H3Index index = sexpStringToH3(h3, i);
    int validity = isValidCell(index);
    SET_INTEGER_ELT(out, i, validity);
  }

  UNPROTECT(1);
  return out;
}

SEXP h3rIsResClassIII(SEXP h3) {
  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(INTSXP, n));

  for(i = 0; i < n; i++) {
    H3Index index = sexpStringToH3(h3, i);
    int classIII = isResClassIII(index);
    SET_INTEGER_ELT(out, i, classIII);
  }

  UNPROTECT(1);
  return out;
}

SEXP h3rIsPentagon(SEXP h3) {
  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(INTSXP, n));

  for(i = 0; i < n; i++) {
    H3Index index = sexpStringToH3(h3, i);
    int pentagon = isPentagon(index);
    SET_INTEGER_ELT(out, i, pentagon);
  }

  UNPROTECT(1);
  return out;
}
