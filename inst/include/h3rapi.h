
#ifndef R_H3R_API_H
#define R_H3R_API_H

#include <R.h>
#include <Rinternals.h>
#include <Rconfig.h>
#include <R_ext/Rdynload.h>

// #include "h3api.h"
// #include <h3api.h>
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


  // Indexing
  inline SEXP attribute_hidden h3rLatLngToCell(SEXP lat, SEXP lon, SEXP res) {
    SEXP(*fun)(SEXP, SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP, SEXP)) R_GetCCallable("h3r", "h3rLatLngToCell");
    return fun(lat, lon, res);
  }

  inline SEXP attribute_hidden h3rDirectionForNeighbor(SEXP origin, SEXP destination) {
    SEXP(*fun)(SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rDirectionForNeighbor");
    return fun(origin, destination);
  }

  inline SEXP attribute_hidden h3rCellToBoundary(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rCellToBoundary");
    return fun(h3);
  }


  // Inspection
  inline SEXP attribute_hidden h3rGetResolution(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rGetResolution");
    return fun(h3);
  }

  inline SEXP attribute_hidden h3rGetBaseCellNumber(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rGetBaseCellNumber");
    return fun(h3);
  }

  inline SEXP attribute_hidden h3rIsValidCell(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rIsValidCell");
    return fun(h3);
  }

  inline SEXP attribute_hidden h3rIsResClassIII(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rIsResClassIII");
    return fun(h3);
  }

  inline SEXP attribute_hidden h3rIsPentagon(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rIsPentagon");
    return fun(h3);
  }


  // Traversal


  // Hierarchy
  inline SEXP attribute_hidden h3rCellToParent(SEXP h3, SEXP parentRes) {
    SEXP(*fun)(SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rCellToParent");
    return fun(h3, parentRes);
  }

  inline SEXP attribute_hidden h3rCellToChildren(SEXP h3, SEXP childRes) {
    SEXP(*fun)(SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rCellToChildren");
    return fun(h3, childRes);
  }


  // Regions


  // Directed Edges


  // Vertexes


  // Miscellaneous
  inline SEXP attribute_hidden h3rGreatCircleDistanceRads(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    SEXP(*fun)(SEXP, SEXP, SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP, SEXP, SEXP)) R_GetCCallable("h3r","h3rGreatCircleDistanceRads");
    return fun(aLats, aLons, bLats, bLons);
  }

  inline SEXP attribute_hidden h3rGreatCircleDistanceM(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    SEXP(*fun)(SEXP, SEXP, SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP, SEXP, SEXP)) R_GetCCallable("h3r","h3GreatCircleDistanceM");
    return fun(aLats, aLons, bLats, bLons);
  }

  inline SEXP attribute_hidden h3rGreatCircleDistanceKm(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    SEXP(*fun)(SEXP, SEXP, SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP, SEXP, SEXP)) R_GetCCallable("h3r","h3rGreatCircleDistanceKm");
    return fun(aLats, aLons, bLats, bLons);
  }

#ifdef __cplusplus
}


namespace h3r {

  // Indexing
  inline SEXP latLngToCell(SEXP lat, SEXP lon, SEXP res) {
    return h3rLatLngToCell(lat, lon, res);
  }

  inline SEXP directionForNeighbor(SEXP origin, SEXP destination) {
    return h3rDirectionForNeighbor(origin, destination);
  }

  inline SEXP cellToBoundary(SEXP h3) {
    return h3rCellToBoundary(h3);
  }

  // Inspection
  inline SEXP getResolution(SEXP h3) {
    return h3rgetResolution(h3);
  }

  inline SEXP getBaseCellNumber(SEXP h3) {
    return h3rGetBaseCellNumber(h3);
  }

  inline SEXP isValidCell(SEXP h3) {
    return h3rIsValidCell(h3);
  }

  inline SEXP isResClassIII(SEXP h3) {
    return h3rIsResClassIII(h3);
  }

  inline SEXP isPentagon(SEXP h3) {
    return h3rIsPentagon(h3);
  }

  // Traversal


  // Hierarchy
  inline SEXP cellToParent(SEXP h3, SEXP parentRes) {
    return h3rCellToParent(h3, parentRes);
  }

  inline SEXP cellToChildren(SEXP h3, SEXP childRes) {
    return h3rCellToChildren(h3, childRes);
  }

  // Regions


  // Directed Edges


  // Vertexes


  // Miscellaneous
  inline SEXP greatCircleDistanceRads(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    return h3rGreatCircleDistanceRads(aLats, aLons, bLats, bLons);
  }

  inline SEXP greatCircleDistanceM(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    return h3rGreatCircleDistanceM(aLats, aLons, bLats, bLons);
  }

  inline SEXP greatCircleDistanceKm(SEXP aLats, SEXP aLons, SEXP bLats, SEXP bLons) {
    return h3rGreatCircleDistanceKm(aLats, aLons, bLats, bLons);
  }
}


#endif  // __cplusplus

#endif // R_H3R_API_H
