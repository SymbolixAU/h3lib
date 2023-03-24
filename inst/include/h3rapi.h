
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

// Forwarding some useful structures
typedef enum {
/** H3 digit in center */
CENTER_DIGIT = 0,
  /** H3 digit in k-axes direction */
  K_AXES_DIGIT = 1,
  /** H3 digit in j-axes direction */
  J_AXES_DIGIT = 2,
  /** H3 digit in j == k direction */
  JK_AXES_DIGIT = J_AXES_DIGIT | K_AXES_DIGIT, /* 3 */
  /** H3 digit in i-axes direction */
  I_AXES_DIGIT = 4,
  /** H3 digit in i == k direction */
  IK_AXES_DIGIT = I_AXES_DIGIT | K_AXES_DIGIT, /* 5 */
  /** H3 digit in i == j direction */
  IJ_AXES_DIGIT = I_AXES_DIGIT | J_AXES_DIGIT, /* 6 */
  /** H3 digit in the invalid direction */
  INVALID_DIGIT = 7,
  /** Valid digits will be less than this value. Same value as INVALID_DIGIT.
   */
  NUM_DIGITS = INVALID_DIGIT,
  /** Child digit which is skipped for pentagons */
  PENTAGON_SKIPPED_DIGIT = K_AXES_DIGIT /* 1 */
} Direction;

typedef uint64_t H3Index;

typedef struct {
  double lat;  ///< latitude in radians
  double lng;  ///< longitude in radians
} LatLng;

typedef struct {
  int i;  ///< i component
  int j;  ///< j component
} CoordIJ;


inline double degsToRads(double degrees) {
  double(*fun)(double) =
    (double(*)(double)) R_GetCCallable("h3r", "degsToRads");
  return fun(degrees);
}

inline double radsToDegs(double degrees) {
  double(*fun)(double) =
    (double(*)(double)) R_GetCCallable("h3r", "radsToDegs");
  return fun(degrees);
}


inline int latLngToCell(const LatLng *g, int res, H3Index *out) {
  int(*fun)(const LatLng*, int, H3Index*) =
    (int(*)(const LatLng*, int, H3Index*)) R_GetCCallable("h3r","latLngToCell");
  return fun(g, res, out);
}

inline Direction directionForNeighbor(H3Index origin, H3Index destination) {
  Direction(*fun)(H3Index, H3Index) =
    (Direction(*)(H3Index, H3Index)) R_GetCCallable("h3r", "directionForNeighbor");
  return fun(origin, destination);
}

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

  inline SEXP attribute_hidden gridDisk(SEXP h3, SEXP k) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridDisk");
    return fun(h3, k);
  }

  inline SEXP attribute_hidden maxGridDiskSize(SEXP k) {
    SEXP(*fun)(SEXP) = (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rMaxGridDiskSize");
    return fun(k);
  }

  inline SEXP attribute_hidden gridDiskDistances(SEXP h3, SEXP k) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridDiskDistances");
    return fun(h3, k);
  }

  inline SEXP attribute_hidden gridDiskUnsafe(SEXP h3, SEXP k) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridDiskUnsafe");
    return fun(h3, k);
  }

  inline SEXP attribute_hidden gridDiskDistancesUnsafe(SEXP h3, SEXP k) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridDiskDistancesUnsafe");
    return fun(h3, k);
  }

  inline SEXP attribute_hidden gridDiskDistancesSafe(SEXP h3, SEXP k) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridDiskDistancesSafe");
    return fun(h3, k);
  }

  inline SEXP attribute_hidden gridRingUnsafe(SEXP h3, SEXP k) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridRingUnsafe");
    return fun(h3, k);
  }

  inline SEXP attribute_hidden gridPathCells(SEXP origH3, SEXP destH3) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridPathCells");
    return fun(origH3, destH3);
  }

  inline SEXP attribute_hidden gridPathCellsSize(SEXP origH3, SEXP destH3) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridPathCellsSize");
    return fun(origH3, destH3);
  }

  inline SEXP attribute_hidden gridDistance(SEXP origH3, SEXP destH3) {
    SEXP(*fun)(SEXP, SEXP) = (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rGridDistance");
    return fun(origH3, destH3);
  }


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
  inline SEXP attribute_hidden h3rAreNeighborCells(SEXP origH3, SEXP destH3) {
    SEXP(*fun)(SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rAreNeighborCells");
    return fun(origH3, destH3);
  }

  inline SEXP attribute_hidden h3rCellsToDirectedEdge(SEXP origH3, SEXP destH3) {
    SEXP(*fun)(SEXP, SEXP) =
      (SEXP(*)(SEXP, SEXP)) R_GetCCallable("h3r", "h3rCellsToDirectedEdge");
    return fun(origH3, destH3);
  }

  inline SEXP attribute_hidden h3rIsValidDirectedEdge(SEXP edge) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rIsValidDirectedEdge");
    return fun(edge);
  }

  inline SEXP attribute_hidden h3rGetDirectedEdgeOrigin(SEXP edge) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rGetDirectedEdgeOrigin");
    return fun(edge);
  }

  inline SEXP attribute_hidden h3rGetDirectedEdgeDestination(SEXP edge) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rGetDirectedEdgeDestination");
    return fun(edge);
  }

  inline SEXP attribute_hidden h3rDirectedEdgeToCells(SEXP edge) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rDirectedEdgeToCells");
    return fun(edge);
  }

  inline SEXP attribute_hidden h3rOriginToDirectedEdges(SEXP origH3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rOriginToDirectedEdges");
    return fun(origH3);
  }

  // Vertexes


  // Miscellaneous
  inline SEXP attribute_hidden h3rDegsToRads(SEXP deg) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rDegsToRads");
    return fun(deg);
  }

  inline SEXP attribute_hidden h3rRadsToDegs(SEXP rad) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r", "h3rRadsToDegs");
    return fun(rad);
  }

  inline SEXP attribute_hidden getHexagonAreaAvgM2(SEXP res) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rGetHexagonAreaAvgM2");
    return fun(res);
  }

  inline SEXP attribute_hidden getHexagonAreaAvgKm2(SEXP res) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rGetHexagonAreaAvgKm2");
    return fun(res);
  }

  inline SEXP attribute_hidden cellAreaRads2(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rCellAreaRads2");
    return fun(h3);
  }

  inline SEXP attribute_hidden cellAreaM2(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rCellAreaM2");
    return fun(h3);
  }

  inline SEXP attribute_hidden cellAreaKm2(SEXP h3) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rCellAreaKm2");
    return fun(h3);
  }

  inline SEXP attribute_hidden getHexagonEdgeLengthAvgM(SEXP res) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rGetHexagonEdgeLengthAvgM");
    return fun(res);
  }

  inline SEXP attribute_hidden getHexagonEdgeLengthAvgKm(SEXP res) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rGetHexagonEdgeLengthAvgKm");
    return fun(res);
  }

  inline SEXP attribute_hidden edgeLengthRads(SEXP edge) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rEdgeLengthRads");
    return fun(edge);
  }

  inline SEXP attribute_hidden edgeLengthM(SEXP edge) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rEdgeLengthM");
    return fun(edge);
  }

  inline SEXP attribute_hidden edgeLengthKm(SEXP edge) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rEdgeLengthKm");
    return fun(edge);
  }

  inline SEXP attribute_hidden getNumCells(SEXP res) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rGetNumCells");
    return fun(res);
  }

  inline SEXP attribute_hidden getRes0Cells() {
    SEXP(*fun)() =
      (SEXP(*)()) R_GetCCallable("h3r","h3rGetRes0Cells");
    return fun();
  }

  inline SEXP attribute_hidden res0CellCount() {
    SEXP(*fun)() =
      (SEXP(*)()) R_GetCCallable("h3r","h3rRes0CellCount");
    return fun();
  }

  inline SEXP attribute_hidden getPentagons(SEXP res) {
    SEXP(*fun)(SEXP) =
      (SEXP(*)(SEXP)) R_GetCCallable("h3r","h3rGetPentagons");
    return fun(res);
  }

  inline SEXP attribute_hidden pentagonCount() {
    SEXP(*fun)() =
      (SEXP(*)()) R_GetCCallable("h3r","h3rPentagonCount");
    return fun();
  }

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

  inline SEXP gridDisk(SEXP h3, SEXP k) {
    return h3rGridDisk(h3, k);
  }

  inline SEXP maxGridDiskSize(SEXP k) {
    return h3rMaxGridDiskSize(k);
  }

  inline SEXP gridDiskDistances(SEXP h3, SEXP k) {
    return h3rGridDiskDistances(h3, k);
  }

  inline SEXP gridDiskUnsafe(SEXP h3, SEXP k) {
    return h3rGridDiskUnsafe(h3, k);
  }

  inline SEXP gridDiskDistancesUnsafe(SEXP h3, SEXP k) {
    return h3rGridDiskDistancesUnsafe(h3, k);
  }

  inline SEXP gridDiskDistancesSafe(SEXP h3, SEXP k) {
    return h3rGridDiskDistancesSafe(h3, k);
  }

  inline SEXP gridRingUnsafe(SEXP h3, SEXP k) {
    return h3rGridRingUnsafe(h3, k);
  }

  inline SEXP gridPathCells(SEXP origH3, SEXP destH3) {
    return h3rGridPathCells(origH3, destH3);
  }

  inline SEXP gridPathCellsSize(SEXP origH3, SEXP destH3) {
    return h3rGridPathCellsSize(origH3, destH3);
  }

  inline SEXP gridDistance(SEXP origH3, SEXP destH3) {
    return h3rGridDistance(origH3, destH3);
  }

  // Hierarchy
  inline SEXP cellToParent(SEXP h3, SEXP parentRes) {
    return h3rCellToParent(h3, parentRes);
  }

  inline SEXP cellToChildren(SEXP h3, SEXP childRes) {
    return h3rCellToChildren(h3, childRes);
  }

  // Regions


  // Directed Edges
  inline SEXP areNeighborCells(SEXP origH3, SEXP destH3) {
    return h3rDegsToRads(origH3, destH3);
  }

  inline SEXP cellsToDirectedEdge(SEXP origH3, SEXP destH3) {
    return h3rCellsToDirectedEdge(origH3, destH3);
  }

  inline SEXP isValidDirectedEdge(SEXP edge) {
    return h3rIsValidDirectedEdge(edge);
  }

  inline SEXP getDirectedEdgeOrigin(SEXP edge) {
    return h3rGetDirectedEdgeOrigin(edge);
  }

  inline SEXP getDirectedEdgeDestination(SEXP edge) {
    return h3rGetDirectedEdgeDestination(edge);
  }

  inline SEXP directedEdgeToCells(SEXP edge) {
    return h3rDirectedEdgeToCells(edge);
  }

  inline SEXP originToDirectedEdges(SEXP origH3) {
    return h3rOriginToDirectedEdges(origH3);
  }

  // Vertexes


  // Miscellaneous
  inline SEXP degsToRads(SEXP deg) {
    return h3rDegsToRads(deg);
  }

  inline SEXP radsToDegs(SEXP rad) {
    return h3rRadsToDegs(rad);
  }

  inline SEXP getHexagonAreaAvgM2(SEXP res) {
    return h3rGetHexagonAreaAvgM2(res);
  }

  inline SEXP getHexagonAreaAvgKm2(SEXP res) {
    return h3rGetHexagonAreaAvgKm2(res);
  }

  inline SEXP cellAreaRads2(SEXP h3) {
    return h3rCellAreaRads2(h3);
  }

  inline SEXP cellAreaM2(SEXP h3) {
    return h3rCellAreaM2(h3);
  }

  inline SEXP cellAreaKm2(SEXP h3) {
    return h3rCellAreaKm2(h3);
  }

  inline SEXP getHexagonEdgeLengthAvgM(SEXP res) {
    return h3rGetHexagonEdgeLengthAvgM(res);
  }

  inline SEXP getHexagonEdgeLengthAvgKm(SEXP res) {
    return h3rGetHexagonEdgeLengthAvgKm(res);
  }

  inline SEXP edgeLengthRads(SEXP edge) {
    return h3rEdgeLengthRads(edge);
  }

  inline SEXP edgeLengthM(SEXP edge) {
    return h3rEdgeLengthM(edge);
  }

  inline SEXP edgeLengthKm(SEXP edge) {
    return h3rEdgeLengthKm(edge);
  }

  inline SEXP getNumCells(SEXP res) {
    return h3rGetNumCells(res);
  }

  inline SEXP getRes0Cells() {
    return h3rGetRes0Cells();
  }

  inline SEXP res0CellCount() {
    return h3rRes0CellCount();
  }

  inline SEXP getPentagons(SEXP res) {
    return h3rGetPentagons(res);
  }

  inline SEXP pentagonCount() {
    return h3rPentagonCount();
  }

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
