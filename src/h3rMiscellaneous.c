

// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3api.h"
#include "algos.h"

#include "h3rUtils.h"


SEXP h3rGreatCircleDistance(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons, int distType) {
  R_xlen_t n = Rf_length(aLats);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(REALSXP, n));

  LatLng a;
  LatLng b;

  for( i = 0; i < n; i++ ) {
    sexpToLatLng(&a, aLats, aLons, i);
    sexpToLatLng(&b, bLats, bLons, i);
    if( distType == 0) {
      SET_REAL_ELT(out, i, greatCircleDistanceRads(&a, &b));
    } else if (distType == 1) {
      SET_REAL_ELT(out, i, greatCircleDistanceM(&a, &b));
    } else {
      SET_REAL_ELT(out, i, greatCircleDistanceKm(&a, &b));
    }

  }

  UNPROTECT(1);
  return out;
}

SEXP h3rGreatCircleDistanceRads(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
  return h3rGreatCircleDistance(aLats, aLons, bLats, bLons, 0);
}

SEXP h3rGreatCircleDistanceM(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
  return h3rGreatCircleDistance(aLats, aLons, bLats, bLons, 1);
}

SEXP h3rGreatCircleDistanceKm(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
  return h3rGreatCircleDistance(aLats, aLons, bLats, bLons, 2);
}
