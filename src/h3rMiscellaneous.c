

// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3api.h"
#include "algos.h"

#include "h3rUtils.h"

// I mean I _could_ just do the matchs directly on the SEXP
// rather than call the H3 library...
SEXP h3rDegsToRads(SEXP degrees) {

  R_xlen_t n = Rf_xlength(degrees);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(REALSXP, n));

  double *dblDeg = REAL(degrees);

  for( i = 0; i < n; i++ ) {
    SET_REAL_ELT(out, i, degsToRads(dblDeg[i]));
  }

  UNPROTECT(1);
  return out;
}

SEXP h3rRadsToDegs(SEXP rads) {
  R_xlen_t n = Rf_xlength(rads);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(REALSXP, n));

  double *dblRads = REAL(rads);

  for( i = 0; i < n; i++ ) {
    SET_REAL_ELT(out, i, radsToDegs(dblRads[i]));
  }

  UNPROTECT(1);
  return out;
}

SEXP h3rCellArea(SEXP h3, int areaType) {
  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;

  SEXP out = PROTECT(Rf_allocVector(REALSXP, n));

  H3Index h;
  double area;

  for( i = 0; i < n; i++ ) {
    h = sexpStringToH3(h3, i);
    if(areaType == 0) {
      cellAreaRads2(h, &area);
      SET_REAL_ELT(out, i, area);
    } else if (areaType == 1) {
      cellAreaM2(h, &area);
      SET_REAL_ELT(out, i, area);
    } else {
      cellAreaKm2(h, &area);
      SET_REAL_ELT(out, i, area);
    }

  }

  UNPROTECT(1);
  return out;
}

SEXP h3rCellAreaRads2(SEXP h3) {
  return h3rCellArea(h3, 0);
}

SEXP h3rCellAreaM2(SEXP h3) {
  return h3rCellArea(h3, 1);
}

SEXP h3rCellAreaKm2(SEXP h3) {
  return h3rCellArea(h3, 2);
}

SEXP h3rGreatCircleDistance(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons, int distType) {
  R_xlen_t n = Rf_xlength(aLats);
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
