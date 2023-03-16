
// #define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rdefines.h>

#include "h3api.h"
#include "algos.h"

#include "h3rUtils.h"

// SEXP h3StringToH3(SEXP h) {
//   R_xlen_t n = Rf_xlength(h);
//
//   SEXP h3 = PROTECT(Rf_allocVector(REALSXP, n));
//   H3Index* h3Index = (H3Index*) REAL(h3);
//
//   R_xlen_t i;
//   // SEXP h3;
//   for( i = 0; i < n; i++ ) {
//     stringToH3(CHAR(STRING_ELT(h, i)), &h3Index[i]);
//   }
//
//   UNPROTECT(1);
//   return h3;
// }
//
// SEXP h3H3ToString(SEXP h) {
//
//   R_xlen_t n = Rf_xlength(h);
//   H3Index* h3 = (H3Index*) REAL(h);
//
//   SEXP result = PROTECT(Rf_allocVector(STRSXP, n));
//
//   char str[17];
//
//   R_xlen_t i;
//   for( i = 0; i < n; i++ ) {
//     h3ToString(h3[i], str, sizeof(str));
//     SET_STRING_ELT(result, i, Rf_mkChar(str));
//   }
//
//   UNPROTECT(1);
//   return result;
// }

// SEXP h3DirectionForNeighbor(SEXP origin, SEXP destination) {
//
//     // TODO:
//     // origin && destination to H3Index;
//     // call directionForNeighbor
//     // convert direction to SEXP
//     // return
//     R_xlen_t n = Rf_xlength(origin);
//     H3Index* h3Origin = (H3Index*) REAL(origin);
//     H3Index* h3Destination = (H3Index*) REAL(destination);
//
//     SEXP result = PROTECT(Rf_allocVector(INTSXP, n));
//
//     R_xlen_t i;
//     for( i = 0; i < n; i++ ) {
//       Direction d = directionForNeighbor(h3Origin[i], h3Destination[i]);
//       SET_INTEGER_ELT(result, i, d);
//     }
//
//     UNPROTECT(1);
//     return result;
// }

// TODO:
// forward the H3-C calls as-is
// provide vectorised SEXP versions



SEXP h3rLatLngToCell(SEXP lat, SEXP lon, SEXP res) {

  R_xlen_t n = Rf_xlength(lat);
  R_xlen_t i;
  SEXP cells = PROTECT(Rf_allocVector(STRSXP, n));

  LatLng latLng;
  H3Index h3Index;
  int ires = INTEGER(res)[0];
  char str[17];

  for( i = 0; i < n; i++ ) {

    sexpToLatLng(&latLng, lat, lon, i);

    latLngToCell(&latLng, ires, &h3Index);
    h3ToString(h3Index, str, 17);

    SET_STRING_ELT(cells, i, Rf_mkChar(str));
  }

  UNPROTECT(1);
  return cells;
}


SEXP h3rCellToLatLng(SEXP h3) {

  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;

  LatLng ll;

  SEXP lats = PROTECT(Rf_allocVector(REALSXP, n));
  SEXP lons = PROTECT(Rf_allocVector(REALSXP, n));

  for( i = 0; i < n; i++ ) {
    H3Index index = sexpStringToH3(h3, i);
    cellToLatLng(index, &ll);
    latLngToSexp(&ll, lats, lons, i);
  }

  SEXP res = latLngList(lats, lons);
  UNPROTECT(2);

  return res;
}


SEXP h3rCellToBoundary(SEXP h3) {
  R_xlen_t n = Rf_xlength(h3);
  R_xlen_t i;
  SEXP names = PROTECT(Rf_allocVector(STRSXP, n));

  // TODO:
  // what structure should be returned?
  // - list of named-lists ?
  // - data.frame with h3, lat, lng columns?
  H3Index index;
  CellBoundary cb;
  LatLng ll;

  SEXP res = PROTECT(Rf_allocVector(VECSXP, n)); // store he results in a list
  // where each element be named as per the cell, adn the valeus will be the lon/lat

  for( i = 0; i < n; i++ ) {

    H3Index index = sexpStringToH3(h3, i);

    cellToBoundary(index, &cb);
    SEXP lst = cellBoundaryToList(&cb);

    SET_STRING_ELT(names, i, STRING_ELT(h3, i));
    SET_VECTOR_ELT(res, i, lst);
  }

  Rf_setAttrib(res, R_NamesSymbol, names);

  UNPROTECT(2);
  return res;
}



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

// SEXP h3maxGridDiskSize(SEXP k) {
//
//   R_xlen_t n = Rf_length(k);
//   R_xlen_t i;
//
//   SEXP out = PROTECT(Rf_allocVector(INTSXP, n));
//
//   for( i = 0; i < n; i++) {
//     int kRing = INTEGER_ELT(k, i);
//
//
//   }
//
//   UNPROTECT(1);
//   return out;
//
// }

// SEXP h3gridDiskUnsafe(SEXP origins, SEXP k) {
//
//   R_xlen_t n = Rf_length(origins);
//   R_xlen_t i;
//
//   SEXP result = PROTECT(Rf_allocVector(STRSXP, n));
//   int64_t outSize;
//
//   for(i = 0; i < n; i++) {
//
//     H3Index origin = sexpStringToH3(origins, i);
//
//     int this_k = INTEGER_ELT(k, i);
//     maxGridDiskSize(this_k, &outSize);
//
//     H3Index out[outSize];
//     gridDiskUnsafe(origin, this_k, &out);
//
//
//   }
//
//   unprotect(1);
//   return result;
//
// }


