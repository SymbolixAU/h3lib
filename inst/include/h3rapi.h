
#ifndef R_H3R_API_H
#define R_H3R_API_H

#include <R.h>
#include <Rinternals.h>
#include <Rconfig.h>
#include <R_ext/Rdynload.h>


// #include "coordijk.h"

#ifdef HAVE_VISIBILITY_ATTRIBUTE
# define attribute_hidden __attribute__ ((visibility ("hidden")))
#else
# define attribute_hidden
#endif

#ifdef __cplusplus
extern "C" {
#endif

// typedef enum {
// /** H3 digit in center */
// CENTER_DIGIT = 0,
//   /** H3 digit in k-axes direction */
//   K_AXES_DIGIT = 1,
//   /** H3 digit in j-axes direction */
//   J_AXES_DIGIT = 2,
//   /** H3 digit in j == k direction */
//   JK_AXES_DIGIT = J_AXES_DIGIT | K_AXES_DIGIT, /* 3 */
//   /** H3 digit in i-axes direction */
//   I_AXES_DIGIT = 4,
//   /** H3 digit in i == k direction */
//   IK_AXES_DIGIT = I_AXES_DIGIT | K_AXES_DIGIT, /* 5 */
//   /** H3 digit in i == j direction */
//   IJ_AXES_DIGIT = I_AXES_DIGIT | J_AXES_DIGIT, /* 6 */
//   /** H3 digit in the invalid direction */
//   INVALID_DIGIT = 7,
//   /** Valid digits will be less than this value. Same value as INVALID_DIGIT.
//    */
//   NUM_DIGITS = INVALID_DIGIT,
//   /** Child digit which is skipped for pentagons */
//   PENTAGON_SKIPPED_DIGIT = K_AXES_DIGIT /* 1 */
// } Direction;
//
// typedef uint64_t H3Index;
//
// typedef struct {
//   double lat;  ///< latitude in radians
//   double lng;  ///< longitude in radians
// } LatLng;
//
// typedef struct {
//   int i;  ///< i component
//   int j;  ///< j component
// } CoordIJ;

  inline SEXP attribute_hidden h3r_latLngToCell(SEXP lat, SEXP lon, SEXP res) {
    SEXP(*fun)(SEXP, SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP, SEXP)) R_GetCCallable("h3r", "h3r_latLngToCell");
    return fun(lat, lon, res);
  }

  inline SEXP attribute_hidden h3r_directionForNeighbor(SEXP origin, SEXP destination) {
    SEXP(*fun)(SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3r_directionForNeighbor");
    return fun(origin, destination);
  }

  inline SEXP attribute_hidden h3r_cellToBoundary(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3r_cellToBoundary");
    return fun(h3);
  }

  inline SEXP attribute_hidden h3r_greatCircleDistanceRads(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3r_greatCircleDistanceRads");
    return fun(aLats, aLons, bLats, bLons);
  }

  inline SEXP attribute_hidden h3r_greatCircleDistanceM(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3r_greatCircleDistanceM");
    return fun(aLats, aLons, bLats, bLons);
  }

  inline SEXP attribute_hidden h3r_greatCircleDistanceKm(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3r_greatCircleDistanceKm");
    return fun(aLats, aLons, bLats, bLons);
  }

#ifdef __cplusplus
}


namespace h3r {
  inline SEXP latLngToCell(SEXP lat, SEXP lon, SEXP res) {
    return h3LatLngToCell(lat, lon, res);
  }

  inline SEXP directionForNeighbor(SEXP origin, SEXP destination) {
    return h3DirectionForNeighbor(origin, destination);
  }

  inline SEXP cellToBoundary(SEXP h3) {
    return h3CellToBoundary(h3);
  }

  inline SEXP greatCircleDistanceRads(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    return h3GreatCircleDistanceRads(aLats, aLons, bLats, bLons);
  }

  inline SEXP greatCircleDistanceM(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    return h3GreatCircleDistanceM(aLats, aLons, bLats, bLons);
  }

  inline SEXP greatCircleDistanceKm(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    return h3GreatCircleDistanceKm(aLats, aLons, bLats, bLons);
  }
}


#endif

#endif // R_H3R_API_H
