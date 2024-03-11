#pragma once

#ifndef R_H3LIB_API_H
#define R_H3LIB_API_H

#include <R.h>
#include <Rinternals.h>
#include <Rconfig.h>
#include <R_ext/Rdynload.h>

/* For uint64_t */
#include <stdint.h>
/* For size_t */
#include <stdlib.h>

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
typedef uint64_t H3Index;

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

#define MAX_CELL_BNDRY_VERTS 10

/** @struct LatLng
    @brief latitude/longitude in radians
*/
typedef struct {
    double lat;  ///< latitude in radians
    double lng;  ///< longitude in radians
} LatLng;

/** @struct CellBoundary
    @brief cell boundary in latitude/longitude
*/
typedef struct {
    int numVerts;                        ///< number of vertices
    LatLng verts[MAX_CELL_BNDRY_VERTS];  ///< vertices in ccw order
} CellBoundary;

/** @struct GeoLoop
 *  @brief similar to CellBoundary, but requires more alloc work
 */
typedef struct {
    int numVerts;
    LatLng *verts;
} GeoLoop;

/** @struct GeoPolygon
 *  @brief Simplified core of GeoJSON Polygon coordinates definition
 */
typedef struct {
    GeoLoop geoloop;  ///< exterior boundary of the polygon
    int numHoles;     ///< number of elements in the array pointed to by holes
    GeoLoop *holes;   ///< interior boundaries (holes) in the polygon
} GeoPolygon;

/** @struct GeoMultiPolygon
 *  @brief Simplified core of GeoJSON MultiPolygon coordinates definition
 */
typedef struct {
    int numPolygons;
    GeoPolygon *polygons;
} GeoMultiPolygon;

/** @struct LinkedLatLng
 *  @brief A coordinate node in a linked geo structure, part of a linked list
 */
typedef struct LinkedLatLng LinkedLatLng;
struct LinkedLatLng {
    LatLng vertex;
    LinkedLatLng *next;
};

/** @struct LinkedGeoLoop
 *  @brief A loop node in a linked geo structure, part of a linked list
 */
typedef struct LinkedGeoLoop LinkedGeoLoop;
struct LinkedGeoLoop {
    LinkedLatLng *first;
    LinkedLatLng *last;
    LinkedGeoLoop *next;
};

/** @struct LinkedGeoPolygon
 *  @brief A polygon node in a linked geo structure, part of a linked list.
 */
typedef struct LinkedGeoPolygon LinkedGeoPolygon;
struct LinkedGeoPolygon {
    LinkedGeoLoop *first;
    LinkedGeoLoop *last;
    LinkedGeoPolygon *next;
};

/** @struct CoordIJ
 * @brief IJ hexagon coordinates
 *
 * Each axis is spaced 120 degrees apart.
 */
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

/** @struct FaceIJK
 * @brief Face number and ijk coordinates on that face-centered coordinate
 * system
 */
typedef struct {
  int face;        ///< face number
  CoordIJK coord;  ///< ijk coordinates on that face
} FaceIJK;

/** @struct Vec2d
 *  @brief 2D floating-point vector
 */
typedef struct {
  double x;  ///< x component
  double y;  ///< y component
} Vec2d;


inline H3Error attribute_hidden latLngToCell( const LatLng *g, int res, H3Index *out ) {
   H3Error (*fun)( const LatLng*, int, H3Index* ) =
    ( H3Error (*)( const LatLng*, int, H3Index* )) R_GetCCallable("h3lib","latLngToCell");
  return fun( g, res, out );
}

inline H3Error attribute_hidden cellToLatLng( H3Index h3, LatLng *g ) {
   H3Error (*fun)( H3Index, LatLng* ) =
    ( H3Error (*)( H3Index, LatLng* )) R_GetCCallable("h3lib","cellToLatLng");
  return fun( h3, g );
}

inline H3Error attribute_hidden cellToBoundary( H3Index h3, CellBoundary *gp ) {
   H3Error (*fun)( H3Index, CellBoundary* ) =
    ( H3Error (*)( H3Index, CellBoundary* )) R_GetCCallable("h3lib","cellToBoundary");
  return fun( h3, gp );
}

inline H3Error attribute_hidden maxGridDiskSize( int k, int64_t *out ) {
   H3Error (*fun)( int, int64_t* ) =
    ( H3Error (*)( int, int64_t* )) R_GetCCallable("h3lib","maxGridDiskSize");
  return fun( k, out );
}

inline H3Error attribute_hidden gridDiskUnsafe( H3Index origin, int k, H3Index *out ) {
   H3Error (*fun)( H3Index, int, H3Index* ) =
    ( H3Error (*)( H3Index, int, H3Index* )) R_GetCCallable("h3lib","gridDiskUnsafe");
  return fun( origin, k, out );
}

inline H3Error attribute_hidden gridDiskDistancesUnsafe( H3Index origin, int k, H3Index *out, int *distances ) {
   H3Error (*fun)( H3Index, int, H3Index*, int* ) =
    ( H3Error (*)( H3Index, int, H3Index*, int* )) R_GetCCallable("h3lib","gridDiskDistancesUnsafe");
  return fun( origin, k, out, distances );
}

inline H3Error attribute_hidden gridDiskDistancesSafe( H3Index origin, int k, H3Index *out, int *distances ) {
   H3Error (*fun)( H3Index, int, H3Index*, int* ) =
    ( H3Error (*)( H3Index, int, H3Index*, int* )) R_GetCCallable("h3lib","gridDiskDistancesSafe");
  return fun( origin, k, out, distances );
}

inline H3Error attribute_hidden gridDisksUnsafe( H3Index *h3Set, int length, int k, H3Index *out ) {
   H3Error (*fun)( H3Index*, int, int, H3Index* ) =
    ( H3Error (*)( H3Index*, int, int, H3Index* )) R_GetCCallable("h3lib","gridDisksUnsafe");
  return fun( h3Set, length, k, out );
}

inline H3Error attribute_hidden gridDisk( H3Index origin, int k, H3Index *out ) {
   H3Error (*fun)( H3Index, int, H3Index* ) =
    ( H3Error (*)( H3Index, int, H3Index* )) R_GetCCallable("h3lib","gridDisk");
  return fun( origin, k, out );
}

inline H3Error attribute_hidden gridDiskDistances( H3Index origin, int k, H3Index *out, int *distances ) {
   H3Error (*fun)( H3Index, int, H3Index*, int* ) =
    ( H3Error (*)( H3Index, int, H3Index*, int* )) R_GetCCallable("h3lib","gridDiskDistances");
  return fun( origin, k, out, distances );
}

inline H3Error attribute_hidden gridRingUnsafe( H3Index origin, int k, H3Index *out ) {
   H3Error (*fun)( H3Index, int, H3Index* ) =
    ( H3Error (*)( H3Index, int, H3Index* )) R_GetCCallable("h3lib","gridRingUnsafe");
  return fun( origin, k, out );
}

inline H3Error attribute_hidden maxPolygonToCellsSize( const GeoPolygon *geoPolygon, int res, uint32_t flags, int64_t *out ) {
   H3Error (*fun)( const GeoPolygon*, int, uint32_t, int64_t* ) =
    ( H3Error (*)( const GeoPolygon*, int, uint32_t, int64_t* )) R_GetCCallable("h3lib","maxPolygonToCellsSize");
  return fun( geoPolygon, res, flags, out );
}

inline H3Error attribute_hidden polygonToCells( const GeoPolygon *geoPolygon, int res, uint32_t flags, H3Index *out ) {
   H3Error (*fun)( const GeoPolygon*, int, uint32_t, H3Index* ) =
    ( H3Error (*)( const GeoPolygon*, int, uint32_t, H3Index* )) R_GetCCallable("h3lib","polygonToCells");
  return fun( geoPolygon, res, flags, out );
}

inline H3Error attribute_hidden cellsToLinkedMultiPolygon( const H3Index *h3Set, const int numHexes, LinkedGeoPolygon *out ) {
   H3Error (*fun)( const H3Index*, const int, LinkedGeoPolygon* ) =
    ( H3Error (*)( const H3Index*, const int, LinkedGeoPolygon* )) R_GetCCallable("h3lib","cellsToLinkedMultiPolygon");
  return fun( h3Set, numHexes, out );
}

inline void attribute_hidden destroyLinkedMultiPolygon( LinkedGeoPolygon *polygon ) {
   void (*fun)( LinkedGeoPolygon* ) =
    ( void (*)( LinkedGeoPolygon* )) R_GetCCallable("h3lib","destroyLinkedMultiPolygon");
  fun( polygon );
}

inline double attribute_hidden degsToRads( double degrees ) {
   double (*fun)( double ) =
    ( double (*)( double )) R_GetCCallable("h3lib","degsToRads");
  return fun( degrees );
}

inline double attribute_hidden radsToDegs( double radians ) {
   double (*fun)( double ) =
    ( double (*)( double )) R_GetCCallable("h3lib","radsToDegs");
  return fun( radians );
}

inline double attribute_hidden greatCircleDistanceRads( const LatLng *a, const LatLng *b ) {
   double (*fun)( const LatLng*, const LatLng* ) =
    ( double (*)( const LatLng*, const LatLng* )) R_GetCCallable("h3lib","greatCircleDistanceRads");
  return fun( a, b );
}

inline double attribute_hidden greatCircleDistanceKm( const LatLng *a, const LatLng *b ) {
   double (*fun)( const LatLng*, const LatLng* ) =
    ( double (*)( const LatLng*, const LatLng* )) R_GetCCallable("h3lib","greatCircleDistanceKm");
  return fun( a, b );
}

inline double attribute_hidden greatCircleDistanceM( const LatLng *a, const LatLng *b ) {
   double (*fun)( const LatLng*, const LatLng* ) =
    ( double (*)( const LatLng*, const LatLng* )) R_GetCCallable("h3lib","greatCircleDistanceM");
  return fun( a, b );
}

inline H3Error attribute_hidden getHexagonAreaAvgKm2( int res, double *out ) {
   H3Error (*fun)( int, double* ) =
    ( H3Error (*)( int, double* )) R_GetCCallable("h3lib","getHexagonAreaAvgKm2");
  return fun( res, out );
}

inline H3Error attribute_hidden getHexagonAreaAvgM2( int res, double *out ) {
   H3Error (*fun)( int, double* ) =
    ( H3Error (*)( int, double* )) R_GetCCallable("h3lib","getHexagonAreaAvgM2");
  return fun( res, out );
}

inline H3Error attribute_hidden cellAreaRads2( H3Index h, double *out ) {
   H3Error (*fun)( H3Index, double* ) =
    ( H3Error (*)( H3Index, double* )) R_GetCCallable("h3lib","cellAreaRads2");
  return fun( h, out );
}

inline H3Error attribute_hidden cellAreaKm2( H3Index h, double *out ) {
   H3Error (*fun)( H3Index, double* ) =
    ( H3Error (*)( H3Index, double* )) R_GetCCallable("h3lib","cellAreaKm2");
  return fun( h, out );
}

inline H3Error attribute_hidden cellAreaM2( H3Index h, double *out ) {
   H3Error (*fun)( H3Index, double* ) =
    ( H3Error (*)( H3Index, double* )) R_GetCCallable("h3lib","cellAreaM2");
  return fun( h, out );
}

inline H3Error attribute_hidden getHexagonEdgeLengthAvgKm( int res, double *out ) {
   H3Error (*fun)( int, double* ) =
    ( H3Error (*)( int, double* )) R_GetCCallable("h3lib","getHexagonEdgeLengthAvgKm");
  return fun( res, out );
}

inline H3Error attribute_hidden getHexagonEdgeLengthAvgM( int res, double *out ) {
   H3Error (*fun)( int, double* ) =
    ( H3Error (*)( int, double* )) R_GetCCallable("h3lib","getHexagonEdgeLengthAvgM");
  return fun( res, out );
}

inline H3Error attribute_hidden edgeLengthRads( H3Index edge, double *length ) {
   H3Error (*fun)( H3Index, double* ) =
    ( H3Error (*)( H3Index, double* )) R_GetCCallable("h3lib","edgeLengthRads");
  return fun( edge, length );
}

inline H3Error attribute_hidden edgeLengthKm( H3Index edge, double *length ) {
   H3Error (*fun)( H3Index, double* ) =
    ( H3Error (*)( H3Index, double* )) R_GetCCallable("h3lib","edgeLengthKm");
  return fun( edge, length );
}

inline H3Error attribute_hidden edgeLengthM( H3Index edge, double *length ) {
   H3Error (*fun)( H3Index, double* ) =
    ( H3Error (*)( H3Index, double* )) R_GetCCallable("h3lib","edgeLengthM");
  return fun( edge, length );
}

inline H3Error attribute_hidden getNumCells( int res, int64_t *out ) {
   H3Error (*fun)( int, int64_t* ) =
    ( H3Error (*)( int, int64_t* )) R_GetCCallable("h3lib","getNumCells");
  return fun( res, out );
}

inline int attribute_hidden res0CellCount( void ) {
   int (*fun)( void ) =
    ( int (*)( void )) R_GetCCallable("h3lib","res0CellCount");
  return fun( );
}

inline H3Error attribute_hidden getRes0Cells( H3Index *out ) {
   H3Error (*fun)( H3Index* ) =
    ( H3Error (*)( H3Index* )) R_GetCCallable("h3lib","getRes0Cells");
  return fun( out );
}

inline int attribute_hidden pentagonCount( void ) {
   int (*fun)( void ) =
    ( int (*)( void )) R_GetCCallable("h3lib","pentagonCount");
  return fun( );
}

inline H3Error attribute_hidden getPentagons( int res, H3Index *out ) {
   H3Error (*fun)( int, H3Index* ) =
    ( H3Error (*)( int, H3Index* )) R_GetCCallable("h3lib","getPentagons");
  return fun( res, out );
}

inline int attribute_hidden getResolution( H3Index h ) {
   int (*fun)( H3Index ) =
    ( int (*)( H3Index )) R_GetCCallable("h3lib","getResolution");
  return fun( h );
}

inline int attribute_hidden getBaseCellNumber( H3Index h ) {
   int (*fun)( H3Index ) =
    ( int (*)( H3Index )) R_GetCCallable("h3lib","getBaseCellNumber");
  return fun( h );
}

inline H3Error attribute_hidden stringToH3( const char *str, H3Index *out ) {
   H3Error (*fun)( const char*, H3Index* ) =
    ( H3Error (*)( const char*, H3Index* )) R_GetCCallable("h3lib","stringToH3");
  return fun( str, out );
}

//  H3Error  h3ToString( H3Index h, char *str, size_t sz ) {
//    H3Error (*fun)( H3Index, char*, size_t ) =
//     ( H3Error (*)( H3Index, char*, size_t )) R_GetCCallable("h3lib","h3ToString");
//   return fun( h, str, sz );
// }

inline int attribute_hidden isValidCell( H3Index h ) {
   int (*fun)( H3Index ) =
    ( int (*)( H3Index )) R_GetCCallable("h3lib","isValidCell");
  return fun( h );
}

inline H3Error attribute_hidden cellToParent( H3Index h, int parentRes, H3Index *parent ) {
   H3Error (*fun)( H3Index, int, H3Index* ) =
    ( H3Error (*)( H3Index, int, H3Index* )) R_GetCCallable("h3lib","cellToParent");
  return fun( h, parentRes, parent );
}

inline H3Error attribute_hidden cellToChildrenSize( H3Index h, int childRes, int64_t *out ) {
   H3Error (*fun)( H3Index, int, int64_t* ) =
    ( H3Error (*)( H3Index, int, int64_t* )) R_GetCCallable("h3lib","cellToChildrenSize");
  return fun( h, childRes, out );
}

inline H3Error attribute_hidden cellToChildren( H3Index h, int childRes, H3Index *children ) {
   H3Error (*fun)( H3Index, int, H3Index* ) =
    ( H3Error (*)( H3Index, int, H3Index* )) R_GetCCallable("h3lib","cellToChildren");
  return fun( h, childRes, children );
}

inline H3Error attribute_hidden cellToCenterChild( H3Index h, int childRes, H3Index *child ) {
   H3Error (*fun)( H3Index, int, H3Index* ) =
    ( H3Error (*)( H3Index, int, H3Index* )) R_GetCCallable("h3lib","cellToCenterChild");
  return fun( h, childRes, child );
}

inline H3Error attribute_hidden cellToChildPos( H3Index child, int parentRes, int64_t *out ) {
   H3Error (*fun)( H3Index, int, int64_t* ) =
    ( H3Error (*)( H3Index, int, int64_t* )) R_GetCCallable("h3lib","cellToChildPos");
  return fun( child, parentRes, out );
}

inline H3Error attribute_hidden childPosToCell( int64_t childPos, H3Index parent, int childRes, H3Index *child ) {
   H3Error (*fun)( int64_t, H3Index, int, H3Index* ) =
    ( H3Error (*)( int64_t, H3Index, int, H3Index* )) R_GetCCallable("h3lib","childPosToCell");
  return fun( childPos, parent, childRes, child );
}

inline H3Error attribute_hidden compactCells( const H3Index *h3Set, H3Index *compactedSet, const int64_t numHexes ) {
   H3Error (*fun)( const H3Index*, H3Index*, const int64_t ) =
    ( H3Error (*)( const H3Index*, H3Index*, const int64_t )) R_GetCCallable("h3lib","compactCells");
  return fun( h3Set, compactedSet, numHexes );
}

inline H3Error attribute_hidden uncompactCellsSize( const H3Index *compactedSet, const int64_t numCompacted, const int res, int64_t *out ) {
   H3Error (*fun)( const H3Index*, const int64_t, const int, int64_t* ) =
    ( H3Error (*)( const H3Index*, const int64_t, const int, int64_t* )) R_GetCCallable("h3lib","uncompactCellsSize");
  return fun( compactedSet, numCompacted, res, out );
}

inline H3Error attribute_hidden uncompactCells( const H3Index *compactedSet, const int64_t numCompacted, H3Index *outSet, const int64_t numOut, const int res ) {
   H3Error (*fun)( const H3Index*, const int64_t, H3Index*, const int64_t, const int ) =
    ( H3Error (*)( const H3Index*, const int64_t, H3Index*, const int64_t, const int )) R_GetCCallable("h3lib","uncompactCells");
  return fun( compactedSet, numCompacted, outSet, numOut, res );
}

inline int attribute_hidden isResClassIII( H3Index h ) {
   int (*fun)( H3Index ) =
    ( int (*)( H3Index )) R_GetCCallable("h3lib","isResClassIII");
  return fun( h );
}

inline int attribute_hidden isPentagon( H3Index h ) {
   int (*fun)( H3Index ) =
    ( int (*)( H3Index )) R_GetCCallable("h3lib","isPentagon");
  return fun( h );
}

inline H3Error attribute_hidden maxFaceCount( H3Index h3, int *out ) {
   H3Error (*fun)( H3Index, int* ) =
    ( H3Error (*)( H3Index, int* )) R_GetCCallable("h3lib","maxFaceCount");
  return fun( h3, out );
}

inline H3Error attribute_hidden getIcosahedronFaces( H3Index h3, int *out ) {
   H3Error (*fun)( H3Index, int* ) =
    ( H3Error (*)( H3Index, int* )) R_GetCCallable("h3lib","getIcosahedronFaces");
  return fun( h3, out );
}

inline H3Error attribute_hidden areNeighborCells( H3Index origin, H3Index destination, int *out ) {
   H3Error (*fun)( H3Index, H3Index, int* ) =
    ( H3Error (*)( H3Index, H3Index, int* )) R_GetCCallable("h3lib","areNeighborCells");
  return fun( origin, destination, out );
}

inline H3Error attribute_hidden cellsToDirectedEdge( H3Index origin, H3Index destination, H3Index *out ) {
   H3Error (*fun)( H3Index, H3Index, H3Index* ) =
    ( H3Error (*)( H3Index, H3Index, H3Index* )) R_GetCCallable("h3lib","cellsToDirectedEdge");
  return fun( origin, destination, out );
}

inline int attribute_hidden isValidDirectedEdge( H3Index edge ) {
   int (*fun)( H3Index ) =
    ( int (*)( H3Index )) R_GetCCallable("h3lib","isValidDirectedEdge");
  return fun( edge );
}

inline H3Error attribute_hidden getDirectedEdgeOrigin( H3Index edge, H3Index *out ) {
   H3Error (*fun)( H3Index, H3Index* ) =
    ( H3Error (*)( H3Index, H3Index* )) R_GetCCallable("h3lib","getDirectedEdgeOrigin");
  return fun( edge, out );
}

inline H3Error attribute_hidden getDirectedEdgeDestination( H3Index edge, H3Index *out ) {
   H3Error (*fun)( H3Index, H3Index* ) =
    ( H3Error (*)( H3Index, H3Index* )) R_GetCCallable("h3lib","getDirectedEdgeDestination");
  return fun( edge, out );
}

inline H3Error attribute_hidden directedEdgeToCells( H3Index edge, H3Index *originDestination ) {
   H3Error (*fun)( H3Index, H3Index* ) =
    ( H3Error (*)( H3Index, H3Index* )) R_GetCCallable("h3lib","directedEdgeToCells");
  return fun( edge, originDestination );
}

inline H3Error attribute_hidden originToDirectedEdges( H3Index origin, H3Index *edges ) {
   H3Error (*fun)( H3Index, H3Index* ) =
    ( H3Error (*)( H3Index, H3Index* )) R_GetCCallable("h3lib","originToDirectedEdges");
  return fun( origin, edges );
}

inline H3Error attribute_hidden directedEdgeToBoundary( H3Index edge, CellBoundary *gb ) {
   H3Error (*fun)( H3Index, CellBoundary* ) =
    ( H3Error (*)( H3Index, CellBoundary* )) R_GetCCallable("h3lib","directedEdgeToBoundary");
  return fun( edge, gb );
}

inline H3Error attribute_hidden cellToVertex( H3Index origin, int vertexNum, H3Index *out ) {
   H3Error (*fun)( H3Index, int, H3Index* ) =
    ( H3Error (*)( H3Index, int, H3Index* )) R_GetCCallable("h3lib","cellToVertex");
  return fun( origin, vertexNum, out );
}

inline H3Error attribute_hidden cellToVertexes( H3Index origin, H3Index *vertexes ) {
   H3Error (*fun)( H3Index, H3Index* ) =
    ( H3Error (*)( H3Index, H3Index* )) R_GetCCallable("h3lib","cellToVertexes");
  return fun( origin, vertexes );
}

inline H3Error attribute_hidden vertexToLatLng( H3Index vertex, LatLng *point ) {
   H3Error (*fun)( H3Index, LatLng* ) =
    ( H3Error (*)( H3Index, LatLng* )) R_GetCCallable("h3lib","vertexToLatLng");
  return fun( vertex, point );
}

inline int attribute_hidden isValidVertex( H3Index vertex ) {
   int (*fun)( H3Index ) =
    ( int (*)( H3Index )) R_GetCCallable("h3lib","isValidVertex");
  return fun( vertex );
}

inline H3Error attribute_hidden gridDistance( H3Index origin, H3Index h3, int64_t *distance ) {
   H3Error (*fun)( H3Index, H3Index, int64_t* ) =
    ( H3Error (*)( H3Index, H3Index, int64_t* )) R_GetCCallable("h3lib","gridDistance");
  return fun( origin, h3, distance );
}

inline H3Error attribute_hidden gridPathCellsSize( H3Index start, H3Index end, int64_t *size ) {
   H3Error (*fun)( H3Index, H3Index, int64_t* ) =
    ( H3Error (*)( H3Index, H3Index, int64_t* )) R_GetCCallable("h3lib","gridPathCellsSize");
  return fun( start, end, size );
}

inline H3Error attribute_hidden gridPathCells( H3Index start, H3Index end, H3Index *out ) {
   H3Error (*fun)( H3Index, H3Index, H3Index* ) =
    ( H3Error (*)( H3Index, H3Index, H3Index* )) R_GetCCallable("h3lib","gridPathCells");
  return fun( start, end, out );
}

inline H3Error attribute_hidden cellToLocalIj( H3Index origin, H3Index h3, uint32_t mode, CoordIJ *out ) {
   H3Error (*fun)( H3Index, H3Index, uint32_t, CoordIJ* ) =
    ( H3Error (*)( H3Index, H3Index, uint32_t, CoordIJ* )) R_GetCCallable("h3lib","cellToLocalIj");
  return fun( origin, h3, mode, out );
}

inline H3Error attribute_hidden localIjToCell( H3Index origin, const CoordIJ *ij, uint32_t mode, H3Index *out ) {
   H3Error (*fun)( H3Index, const CoordIJ*, uint32_t, H3Index* ) =
    ( H3Error (*)( H3Index, const CoordIJ*, uint32_t, H3Index* )) R_GetCCallable("h3lib","localIjToCell");
  return fun( origin, ij, mode, out );
}


// Non-API
inline Direction attribute_hidden directionForNeighbor(H3Index origin, H3Index destination) {
 Direction(*fun)(H3Index, H3Index) =
     (Direction(*)(H3Index, H3Index)) R_GetCCallable("h3lib", "directionForNeighbor");
 return fun(origin, destination);
}

inline void attribute_hidden _geoToClosestFace(const LatLng *g, int *face, double *sqd) {
  void(*fun)(const LatLng*, int*, double*) =
    (void(*)(const LatLng*, int*, double*)) R_GetCCallable("h3lib", "_geoToClosestFace");
  fun(g, face, sqd);
}


#ifdef __cplusplus
}
#endif


#endif // R_H3LIB_API_H
