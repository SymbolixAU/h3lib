
#ifndef R_H3LIB_API_H
#define R_H3LIB_API_H

#include <R.h>
#include <Rinternals.h>
#include <Rconfig.h>
#include <R_ext/Rdynload.h>

// #include "h3api.h" <-- can't include this as it' can't be found by linking packages

#ifdef HAVE_VISIBILITY_ATTRIBUTE
# define attribute_hidden __attribute__ ((visibility ("hidden")))
#else
# define attribute_hidden
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t H3Error;

  /** The number of faces on an icosahedron */
#define NUM_ICOSA_FACES 20
  /** The number of H3 base cells */
#define NUM_BASE_CELLS 122
  /** The number of vertices in a hexagon */
#define NUM_HEX_VERTS 6
  /** The number of vertices in a pentagon */
#define NUM_PENT_VERTS 5
  /** The number of pentagons per resolution **/
#define NUM_PENTAGONS 12

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
  int numVerts;
  LatLng *verts;
} GeoLoop;

typedef struct {
  GeoLoop geoloop;  ///< exterior boundary of the polygon
  int numHoles;     ///< number of elements in the array pointed to by holes
  GeoLoop *holes;   ///< interior boundaries (holes) in the polygon
} GeoPolygon;

typedef struct {
  int numPolygons;
  GeoPolygon *polygons;
} GeoMultiPolygon;


typedef struct LinkedLatLng LinkedLatLng;
struct LinkedLatLng {
  LatLng vertex;
  LinkedLatLng *next;
};

typedef struct LinkedGeoLoop LinkedGeoLoop;
struct LinkedGeoLoop {
  LinkedLatLng *first;
  LinkedLatLng *last;
  LinkedGeoLoop *next;
};


typedef struct LinkedGeoPolygon LinkedGeoPolygon;
struct LinkedGeoPolygon {
  LinkedGeoLoop *first;
  LinkedGeoLoop *last;
  LinkedGeoPolygon *next;
};


typedef struct {
  int i;  ///< i component
  int j;  ///< j component
} CoordIJ;

/** @struct CoordIJK
 * @brief IJK hexagon coordinates
 *
 * Each axis is spaced 120 degrees apart.
 */
typedef struct {
  int i;  ///< i component
  int j;  ///< j component
  int k;  ///< k component
} CoordIJK;

/** @brief CoordIJK unit vectors corresponding to the 7 H3 digits.
 */
static const CoordIJK UNIT_VECS[] = {
  {0, 0, 0},  // direction 0
  {0, 0, 1},  // direction 1
  {0, 1, 0},  // direction 2
  {0, 1, 1},  // direction 3
  {1, 0, 0},  // direction 4
  {1, 0, 1},  // direction 5
  {1, 1, 0}   // direction 6
};

/** @struct FaceIJK
 * @brief Face number and ijk coordinates on that face-centered coordinate
 * system
 */
typedef struct {
  int face;        ///< face number
  CoordIJK coord;  ///< ijk coordinates on that face
} FaceIJK;

/** @struct FaceOrientIJK
 * @brief Information to transform into an adjacent face IJK system
 */
typedef struct {
  int face;            ///< face number
  CoordIJK translate;  ///< res 0 translation relative to primary face
  int ccwRot60;  ///< number of 60 degree ccw rotations relative to primary
  /// face
} FaceOrientIJK;

extern const LatLng faceCenterGeo[NUM_ICOSA_FACES];

// indexes for faceNeighbors table
/** IJ quadrant faceNeighbors table direction */
#define IJ 1
/** KI quadrant faceNeighbors table direction */
#define KI 2
/** JK quadrant faceNeighbors table direction */
#define JK 3

/** Invalid face index */
#define INVALID_FACE -1


// Indexing
inline H3Error latLngToCell(const LatLng *g, int res, H3Index *out) {
  H3Error(*fun)(const LatLng*, int, H3Index*) =
    (H3Error(*)(const LatLng*, int, H3Index*)) R_GetCCallable("h3lib","latLngToCell");
  return fun(g, res, out);
}

inline H3Error cellToLatLng(H3Index h3, LatLng *g) {
  H3Error(*fun)(H3Index, LatLng* ) =
    (H3Error(*)(H3Index, LatLng*)) R_GetCCallable("h3lib", "cellToLatLng");
  return fun(h3, g);
}


inline H3Error cellToBoundary(H3Index h3, CellBoundary *gp) {
  H3Error(*fun)(H3Index, CellBoundary*) =
    (H3Error(*)(H3Index, CellBoundary*)) R_GetCCallable("h3lib", "cellToBoundary");
  return fun(h3, gp);
}


// Inspection
inline int getResolution(H3Index h) {
  int(*fun)(H3Index) =
    (int(*)(H3Index)) R_GetCCallable("h3lib", "getResolution");
  return fun(h);
}

inline int getBaseCellNumber(H3Index h) {
  int(*fun)(H3Index) =
    (int(*)(H3Index)) R_GetCCallable("h3lib", "getBaseCellNumber");
  return fun(h);
}


inline H3Error stringToH3(const char *str, H3Index *out) {
  H3Error(*fun)(const char*, H3Index*) =
    (H3Error(*)(const char*, H3Index*)) R_GetCCallable("h3lib","stringToH3");
  return fun(str, out);
}

inline H3Error h3ToString(H3Index h3, char *str, size_t sz) {
  H3Error(*fun)(H3Index, char*, size_t) =
    (H3Error(*)(H3Index, char*, size_t)) R_GetCCallable("h3lib", "h3ToString");
  return fun(h3, str, sz);
}

inline int isValidCell(H3Index h) {
  int(*fun)(H3Index) =
    (int(*)(H3Index)) R_GetCCallable("h3lib", "isValidCell");
  return fun(h);
}

inline int isResClassIII(H3Index h) {
  int(*fun)(H3Index) =
    (int(*)(H3Index)) R_GetCCallable("h3lib", "isResClassIII");
  return fun(h);
}

inline int isPentagon(H3Index h) {
  int(*fun)(H3Index) =
    (int(*)(H3Index)) R_GetCCallable("h3lib", "isPentagon");
  return fun(h);
}

inline H3Error getIcosahedronFaces(H3Index h, int* out) {
  H3Error(*fun)(H3Index, int*) =
    (H3Error(*)(H3Index, int*)) R_GetCCallable("h3lib", "getIcosahedronFaces");
    return fun(h, out);
}


inline H3Error maxFaceCount(H3Index h, int* out) {
  H3Error(*fun)(H3Index, int*) =
    (H3Error(*)(H3Index, int*)) R_GetCCallable("h3lib", "maxFaceCount");
  return fun(h, out);
}


// Traversal
inline H3Error gridDisk(H3Index origin, int k, H3Index* out) {
  H3Error(*fun)(H3Index, int, H3Index*) =
    (H3Error(*)(H3Index, int, H3Index*)) R_GetCCallable("h3lib", "gridDisk");
  return fun(origin, k, out);
}

inline H3Error maxGridDiskSize(int k, int64_t *out) {
  H3Error(*fun)(int, int64_t*) =
    (H3Error(*)(int, int64_t*)) R_GetCCallable("h3lib", "maxGridDiskSize");
  return fun(k, out);
}

inline H3Error gridDiskDistances(H3Index origin, int k, H3Index* out, int* distances) {
  H3Error(*fun)(H3Index, int, H3Index*, int*) =
    (H3Error(*)(H3Index, int, H3Index*, int*)) R_GetCCallable("h3lib","gridDiskDistances");
  return fun(origin, k, out, distances);
}

inline H3Error gridDiskUnsafe(H3Index origin, int k, H3Index* out) {
  H3Error(*fun)(H3Index, int, H3Index*) =
    (H3Error(*)(H3Index, int, H3Index*)) R_GetCCallable("h3lib","gridDiskUnsafe");
  return fun(origin, k, out);
}

inline H3Error gridDiskDistancesUnsafe(H3Index origin, int k, H3Index* out, int* distances) {
  H3Error(*fun)(H3Index, int, H3Index*, int*) =
    (H3Error(*)(H3Index, int, H3Index*, int*)) R_GetCCallable("h3lib", "gridDiskDistancesUnsafe");
  return fun(origin, k, out, distances);
}

inline H3Error gridDiskDistancesSafe(H3Index origin, int k, H3Index* out, int* distances) {
  H3Error(*fun)(H3Index, int, H3Index*, int*) =
    (H3Error(*)(H3Index, int, H3Index*, int*)) R_GetCCallable("h3lib", "gridDiskDistancesSafe");
  return fun(origin, k, out, distances);
}

inline H3Error gridDisksUnsafe(H3Index* h3Set, int length, int k, H3Index* out) {
  H3Error(*fun)(H3Index*, int, int, H3Index*) =
    (H3Error(*)(H3Index*, int, int, H3Index*)) R_GetCCallable("h3lib", "gridDisksUnsafe");
  return fun(h3Set, length, k, out);
}

inline H3Error gridRingUnsafe(H3Index origin, int k, H3Index* out) {
  H3Error(*fun)(H3Index, int, H3Index*) =
    (H3Error(*)(H3Index, int, H3Index*)) R_GetCCallable("h3lib", "gridRingUnsafe");
  return fun(origin, k, out);
}

inline H3Error gridPathCells(H3Index start, H3Index end, H3Index* out) {
  H3Error(*fun)(H3Index, H3Index, H3Index*) =
    (H3Error(*)(H3Index, H3Index, H3Index*)) R_GetCCallable("h3lib", "gridPathCells");
  return fun(start, end, out);
}

inline H3Error gridPathCellsSize(H3Index start, H3Index end, int64_t *size) {
  H3Error(*fun)(H3Index, H3Index, int64_t*) =
    (H3Error(*)(H3Index, H3Index, int64_t*)) R_GetCCallable("h3lib", "gridPathCellsSize");
  return fun(start, end, size);
}

inline H3Error gridDistance(H3Index origin, H3Index h3, int64_t *distance) {
  H3Error(*fun)(H3Index, H3Index, int64_t*) =
    (H3Error(*)(H3Index, H3Index, int64_t*)) R_GetCCallable("h3lib", "gridDistance");
  return fun(origin, h3, distance);
}

inline H3Error cellToLocalIj(H3Index origin, H3Index h3, uint32_t mode, CoordIJ *out) {
  H3Error(*fun)(H3Index, H3Index, uint32_t, CoordIJ*) =
    (H3Error(*)(H3Index, H3Index, uint32_t, CoordIJ*)) R_GetCCallable("h3lib", "cellToLocalIj");
  return fun(origin, h3, mode, out);
}

inline H3Error localIjToCell(H3Index origin, const CoordIJ *ij, uint32_t mode, H3Index *out) {
  H3Error(*fun)(H3Index, const CoordIJ*, uint32_t, H3Index*) =
    (H3Error(*)(H3Index, const CoordIJ*, uint32_t, H3Index*)) R_GetCCallable("h3lib", "localIjToCell");
  return fun(origin, ij, mode, out);
}

// Hierarchy
inline H3Error cellToParent(H3Index cell, int parentRes, H3Index *parent) {
  H3Error(*fun)(H3Index, int, H3Index*) =
    (H3Error(*)(H3Index, int, H3Index*)) R_GetCCallable("h3lib", "cellToParent");
  return fun(cell, parentRes, parent);
}

inline H3Error cellToChildren(H3Index cell, int childRes, H3Index *children) {
  H3Error(*fun)(H3Index, int, H3Index*) =
    (H3Error(*)(H3Index, int, H3Index*)) R_GetCCallable("h3lib", "cellToChildren");
  return fun(cell, childRes, children);
}

inline H3Error cellToChildrenSize(H3Index cell, int childRes, int64_t *out) {
  H3Error(*fun)(H3Index, int, int64_t*) =
    (H3Error(*)(H3Index, int, int64_t*)) R_GetCCallable("h3lib", "cellToChildrenSize");
  return fun(cell, childRes, out);
}

inline H3Error cellToCenterChild(H3Index cell, int childRes, H3Index *child) {
  H3Error(*fun)(H3Index, int, H3Index*) =
    (H3Error(*)(H3Index, int, H3Index*)) R_GetCCallable("h3lib", "cellToCenterChild");
  return fun(cell, childRes, child);
}

inline H3Error cellToChildPos(H3Index child, int parentRes, int64_t *out) {
  H3Error(*fun)(H3Index, int, int64_t*) =
    (H3Error(*)(H3Index, int, int64_t*)) R_GetCCallable("h3lib", "cellToChildPos");
  return fun(child, parentRes, out);
}

inline H3Error childPosToCell(int64_t childPos, H3Index parent, int childRes, H3Index *child) {
  H3Error(*fun)(int64_t, H3Index, int, H3Index*) =
    (H3Error(*)(int64_t, H3Index, int, H3Index*)) R_GetCCallable("h3lib", "childPosToCell");
  return fun(childPos, parent, childRes, child);
}

inline H3Error compactCells(const H3Index *cellSet, H3Index *compactedSet, const int64_t numCells) {
  H3Error(*fun)(const H3Index*, H3Index*, const int64_t) =
    (H3Error(*)(const H3Index*, H3Index*, const int64_t)) R_GetCCallable("h3lib","compactCells");
  return fun(cellSet, compactedSet, numCells);
}

inline H3Error uncompactCells(const H3Index *compactedSet, const int64_t numCells, H3Index *cellSet, const int64_t maxCells, const int res) {
  H3Error(*fun)(const H3Index*, const int64_t, H3Index*, const int64_t, const int) =
    (H3Error(*)(const H3Index*, const int64_t, H3Index*, const int64_t, const int)) R_GetCCallable("h3lib","uncompactCells");
  return fun(compactedSet, numCells, cellSet, maxCells, res);
}

inline H3Error uncompactCellsSize(const H3Index *compactedSet, const int64_t numCompacted, const int res, int64_t *out) {
  H3Error(*fun)(const H3Index*, const int64_t, const int, int64_t*) =
    (H3Error(*)(const H3Index*, const int64_t, const int, int64_t*)) R_GetCCallable("h3lib","uncompactCellsSize");
  return fun(compactedSet, numCompacted, res, out);
}


// Regions
inline H3Error polygonToCells(const GeoPolygon *geoPolygon, int res, uint32_t flags, H3Index *out) {
  H3Error(*fun)(const GeoPolygon*, int, uint32_t, H3Index*) =
    (H3Error(*)(const GeoPolygon*, int, uint32_t, H3Index*)) R_GetCCallable("h3lib", "polygonToCells");
  return fun(geoPolygon, res, flags, out);
}

inline H3Error maxPolygonToCellsSize(const GeoPolygon *geoPolygon, int res, uint32_t flags, int64_t *out) {
  H3Error(*fun)(const GeoPolygon*, int, uint32_t, int64_t*) =
    (H3Error(*)(const GeoPolygon*, int, uint32_t, int64_t*)) R_GetCCallable("h3lib", "maxPolygonToCellsSize");
  return fun(geoPolygon, res, flags, out);
}

inline H3Error cellsToLinkedMultiPolygon(const H3Index *h3Set, const int numHexes, LinkedGeoPolygon *out) {
  H3Error(*fun)(const H3Index*, const int, LinkedGeoPolygon*) =
    (H3Error(*)(const H3Index*, const int, LinkedGeoPolygon*)) R_GetCCallable("h3lib", "cellsToLinkedMultiPolygon");
  return fun(h3Set, numHexes, out);
}

inline void destroyLinkedMultiPolygon(LinkedGeoPolygon *polygon) {
  void(*fun)(LinkedGeoPolygon*) =
    (void(*)(LinkedGeoPolygon*)) R_GetCCallable("h3lib", "destroyLinkedMultiPolygon");
  fun(polygon);
}

// Directed Edges
inline H3Error areNeighborCells(H3Index origin, H3Index destination, int *out) {
  H3Error(*fun)(H3Index, H3Index, int*) =
    (H3Error(*)(H3Index, H3Index, int*)) R_GetCCallable("h3lib", "areNeighborCells");
  return fun(origin, destination, out);
}

inline H3Error cellsToDirectedEdge(H3Index origin, H3Index destination, H3Index *out) {
  H3Error(*fun)(H3Index, H3Index, H3Index*) =
    (H3Error(*)(H3Index, H3Index, H3Index*)) R_GetCCallable("h3lib", "cellsToDirectedEdge");
  return fun(origin, destination, out);
}

inline int isValidDirectedEdge(H3Index edge) {
  int(*fun)(H3Index) =
    (int(*)(H3Index)) R_GetCCallable("h3lib", "isValidDirectedEdge");
  return fun(edge);
}

inline H3Error getDirectedEdgeOrigin(H3Index edge, H3Index *out) {
  H3Error(*fun)(H3Index, H3Index*) =
    (H3Error(*)(H3Index, H3Index*)) R_GetCCallable("h3lib", "getDirectedEdgeOrigin");
  return fun(edge, out);
}

inline H3Error getDirectedEdgeDestination(H3Index edge, H3Index *out) {
  H3Error(*fun)(H3Index, H3Index*) =
    (H3Error(*)(H3Index, H3Index*)) R_GetCCallable("h3lib", "getDirectedEdgeDestination");
  return fun(edge, out);
}

inline H3Error directedEdgeToCells(H3Index edge, H3Index* originDestination) {
  H3Error(*fun)(H3Index, H3Index*) =
    (H3Error(*)(H3Index, H3Index*)) R_GetCCallable("h3lib", "directedEdgeToCells");
  return fun(edge, originDestination);
}

inline H3Error originToDirectedEdges(H3Index origin, H3Index* edges) {
  H3Error(*fun)(H3Index, H3Index*) =
    (H3Error(*)(H3Index, H3Index*)) R_GetCCallable("h3lib", "originToDirectedEdges");
  return fun(origin, edges);
}

inline H3Error directedEdgeToBoundary(H3Index edge, CellBoundary* gb) {
  H3Error(*fun)(H3Index, CellBoundary*) =
    (H3Error(*)(H3Index, CellBoundary*)) R_GetCCallable("h3lib", "directedEdgeToBoundary");
  return fun(edge, gb);
}


// Vetexes
inline H3Error cellToVertex(H3Index origin, int vertexNum, H3Index *out) {
  H3Error(*fun)(H3Index, int, H3Index*) =
    (H3Error(*)(H3Index, int, H3Index*)) R_GetCCallable("h3lib", "cellToVertex");
  return fun(origin, vertexNum, out);
}

inline H3Error cellToVertexes(H3Index origin, H3Index *out) {
  H3Error(*fun)(H3Index, H3Index*) =
    (H3Error(*)(H3Index, H3Index*)) R_GetCCallable("h3lib", "cellToVertexes");
  return fun(origin, out);
}

inline H3Error vertexToLatLng(H3Index vertex, LatLng *point) {
  H3Error(*fun)(H3Index, LatLng*) =
    (H3Error(*)(H3Index, LatLng*)) R_GetCCallable("h3lib", "vertexToLatLng");
  return fun(vertex, point);
}

inline int isValidVertex(H3Index vertex) {
  int(*fun)(H3Index) =
    (int(*)(H3Index)) R_GetCCallable("h3lib", "isValidVertex");
  return fun(vertex);
}




// Miscellaneous
inline double degsToRads(double degrees) {
  double(*fun)(double) =
    (double(*)(double)) R_GetCCallable("h3lib", "degsToRads");
  return fun(degrees);
}

inline double radsToDegs(double radians) {
  double(*fun)(double) =
    (double(*)(double)) R_GetCCallable("h3lib", "radsToDegs");
  return fun(radians);
}

inline H3Error getHexagonAreaAvgKm2(int res, double *out) {
  H3Error(*fun)(int, double*) =
    (H3Error(*)(int, double*)) R_GetCCallable("h3lib", "getHexagonAreaAvgKm2");
  return fun(res, out);
}

inline H3Error getHexagonAreaAvgM2(int res, double *out) {
  H3Error(*fun)(int, double*) =
    (H3Error(*)(int, double*)) R_GetCCallable("h3lib", "getHexagonAreaAvgM2");
  return fun(res, out);
}

inline H3Error cellAreaRads2(H3Index h, double *out) {
  H3Error(*fun)(H3Index, double*) =
    (H3Error(*)(H3Index, double*)) R_GetCCallable("h3lib", "cellAreaRads2");
  return fun(h, out);
}

inline H3Error cellAreaKm2(H3Index h, double *out) {
  H3Error(*fun)(H3Index, double*) =
    (H3Error(*)(H3Index, double*)) R_GetCCallable("h3lib", "cellAreaKm2");
  return fun(h, out);
}

inline H3Error cellAreaM2(H3Index h, double *out) {
  H3Error(*fun)(H3Index, double*) =
    (H3Error(*)(H3Index, double*)) R_GetCCallable("h3lib", "cellAreaM2");
  return fun(h, out);
}

inline H3Error getHexagonEdgeLengthAvgKm(int res, double *out) {
  H3Error(*fun)(int, double*) =
    (H3Error(*)(int, double*)) R_GetCCallable("h3lib", "getHexagonEdgeLengthAvgKm");
  return fun(res, out);
}

inline H3Error getHexagonEdgeLengthAvgM(int res, double *out) {
  H3Error(*fun)(int, double*) =
    (H3Error(*)(int, double*)) R_GetCCallable("h3lib", "getHexagonEdgeLengthAvgM");
  return fun(res, out);
}


inline H3Error edgeLengthKm(H3Index edge, double *out) {
  H3Error(*fun)(H3Index, double*) =
    (H3Error(*)(H3Index, double*)) R_GetCCallable("h3lib", "edgeLengthKm");
  return fun(edge, out);
}

inline H3Error edgeLengthM(H3Index edge, double *out) {
  H3Error(*fun)(H3Index, double*) =
    (H3Error(*)(H3Index, double*)) R_GetCCallable("h3lib", "edgeLengthM");
  return fun(edge, out);
}

inline H3Error edgeLengthRads(H3Index edge, double *out) {
  H3Error(*fun)(H3Index, double*) =
    (H3Error(*)(H3Index, double*)) R_GetCCallable("h3lib", "edgeLengthRads");
  return fun(edge, out);
}

inline H3Error getNumCells(int res, int64_t *out) {
  H3Error(*fun)(int, int64_t*) =
    (H3Error(*)(int, int64_t*)) R_GetCCallable("h3lib", "getNumCells");
  return fun(res, out);
}


inline H3Error getRes0Cells(H3Index *out) {
  H3Error(*fun)(H3Index*) =
    (H3Error(*)(H3Index*)) R_GetCCallable("h3lib","getRes0Cells");
  return fun(out);
}

inline int res0CellCount() {
  int(*fun)() =
    (int(*)()) R_GetCCallable("h3lib", "res0CellCount");
  return fun();
}

inline H3Error getPentagons(int res, H3Index *out) {
  H3Error(*fun)(int, H3Index*) =
    (H3Error(*)(int, H3Index*)) R_GetCCallable("h3lib", "getPentagons");
  return fun(res, out);
}

inline int pentagonCount() {
  int(*fun)() =
    (int(*)()) R_GetCCallable("h3lib", "pentagonCount");
  return fun();
}

inline double greatCircleDistanceKm(const LatLng *a, const LatLng *b) {
  double(*fun)(const LatLng*, const LatLng*) =
    (double(*)(const LatLng*, const LatLng*)) R_GetCCallable("h3lib", "greatCircleDistanceKm");
  return fun(a, b);
}

inline double greatCircleDistanceM(const LatLng *a, const LatLng *b) {
  double(*fun)(const LatLng*, const LatLng*) =
    (double(*)(const LatLng*, const LatLng*)) R_GetCCallable("h3lib", "greatCircleDistanceM");
  return fun(a, b);
}

inline double greatCircleDistanceRads(const LatLng *a, const LatLng *b) {
  double(*fun)(const LatLng*, const LatLng*) =
    (double(*)(const LatLng*, const LatLng*)) R_GetCCallable("h3lib", "greatCircleDistanceRads");
  return fun(a, b);
}


// Non-API

inline Direction directionForNeighbor(H3Index origin, H3Index destination) {
  Direction(*fun)(H3Index, H3Index) =
    (Direction(*)(H3Index, H3Index)) R_GetCCallable("h3lib", "directionForNeighbor");
  return fun(origin, destination);
}



#ifdef __cplusplus
}


// namespace h3lib {
//
// }


#endif  // __cplusplus

#endif // R_H3LIB_API_H
