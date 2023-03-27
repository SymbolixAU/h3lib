
#ifndef R_H3LIB_API_H
#define R_H3LIB_API_H

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

#define MAX_CELL_BNDRY_VERTS 10

typedef struct {
  double lat;  ///< latitude in radians
  double lng;  ///< longitude in radians
} LatLng;

typedef struct {
  int numVerts;                        ///< number of vertices
  LatLng verts[MAX_CELL_BNDRY_VERTS];  ///< vertices in ccw order
} CellBoundary;

typedef struct {
  int i;  ///< i component
  int j;  ///< j component
} CoordIJ;

inline int stringToH3(const char *str, H3Index *out) {
  int(*fun)(const char*, H3Index*) =
    (int(*)(const char*, H3Index*)) R_GetCCallable("h3lib","stringToH3");
  return fun(str, out);
}

inline int h3ToString(H3Index h3, char *str, size_t sz) {
  int(*fun)(H3Index, char*, size_t) =
    (int(*)(H3Index, char*, size_t)) R_GetCCallable("h3lib", "h3ToString");
  return fun(h3, str, sz);
}

inline double degsToRads(double degrees) {
  double(*fun)(double) =
    (double(*)(double)) R_GetCCallable("h3lib", "degsToRads");
  return fun(degrees);
}

inline double radsToDegs(double degrees) {
  double(*fun)(double) =
    (double(*)(double)) R_GetCCallable("h3lib", "radsToDegs");
  return fun(degrees);
}


inline int latLngToCell(const LatLng *g, int res, H3Index *out) {
  int(*fun)(const LatLng*, int, H3Index*) =
    (int(*)(const LatLng*, int, H3Index*)) R_GetCCallable("h3lib","latLngToCell");
  return fun(g, res, out);
}

inline int cellToLatLng(H3Index h3, LatLng *g) {
  int(*fun)(H3Index, LatLng* ) =
    (int(*)(H3Index, LatLng*)) R_GetCCallable("h3lib", "cellToLatLng");
  return fun(h3, g);
}


inline int cellToBoundary(H3Index h3, CellBoundary *gp) {
  int(*fun)(H3Index, CellBoundary*) =
    (int(*)(H3Index, CellBoundary*)) R_GetCCallable("h3lib", "cellToBoundary");
  return fun(h3, gp);
}

inline int gridPathCellsSize(H3Index start, H3Index end, int64_t *size) {
  int(*fun)(H3Index, H3Index, int64_t*) =
    (int(*)(H3Index, H3Index, int64_t*)) R_GetCCallable("h3lib", "gridPathCellsSize");
  return fun(start, end, size);
}


inline int gridPathCells(H3Index start, H3Index end, H3Index *out) {
  int(*fun)(H3Index, H3Index, H3Index*) =
    (int(*)(H3Index, H3Index, H3Index*)) R_GetCCallable("h3lib", "gridPathCells");
  return fun(start, end, out);
}


inline Direction directionForNeighbor(H3Index origin, H3Index destination) {
  Direction(*fun)(H3Index, H3Index) =
    (Direction(*)(H3Index, H3Index)) R_GetCCallable("h3lib", "directionForNeighbor");
  return fun(origin, destination);
}


#ifdef __cplusplus
}


namespace h3r {

}


#endif  // __cplusplus

#endif // R_H3LIB_API_H
