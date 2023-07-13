// #include "h3api.h"

#include "algos.h" // directionForNeighbor
#include "faceijk.h" // FACEIJK operations
#include "h3Index.h" // _h3ToFaceIjk and _faceIjkToH3

#include <R.h>
#include <Rconfig.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>


/* Define .Call functions */
static const R_CallMethodDef callMethods[] = {
  {NULL,                NULL,                        0}
};

void attribute_visible R_init_h3lib(DllInfo *info)
{
  R_registerRoutines(info, NULL, callMethods, NULL, NULL);

  R_useDynamicSymbols(info, FALSE);


  R_RegisterCCallable("h3lib", "latLngToCell",         (DL_FUNC) &latLngToCell);
  R_RegisterCCallable("h3lib", "cellToLatLng",         (DL_FUNC) &cellToLatLng);
  R_RegisterCCallable("h3lib", "cellToBoundary",         (DL_FUNC) &cellToBoundary);
  R_RegisterCCallable("h3lib", "maxGridDiskSize",         (DL_FUNC) &maxGridDiskSize);
  R_RegisterCCallable("h3lib", "gridDiskUnsafe",         (DL_FUNC) &gridDiskUnsafe);
  R_RegisterCCallable("h3lib", "gridDiskDistancesUnsafe",         (DL_FUNC) &gridDiskDistancesUnsafe);
  R_RegisterCCallable("h3lib", "gridDiskDistancesSafe",         (DL_FUNC) &gridDiskDistancesSafe);
  R_RegisterCCallable("h3lib", "gridDisksUnsafe",         (DL_FUNC) &gridDisksUnsafe);
  R_RegisterCCallable("h3lib", "gridDisk",         (DL_FUNC) &gridDisk);
  R_RegisterCCallable("h3lib", "gridDiskDistances",         (DL_FUNC) &gridDiskDistances);
  R_RegisterCCallable("h3lib", "gridRingUnsafe",         (DL_FUNC) &gridRingUnsafe);
  R_RegisterCCallable("h3lib", "maxPolygonToCellsSize",         (DL_FUNC) &maxPolygonToCellsSize);
  R_RegisterCCallable("h3lib", "polygonToCells",         (DL_FUNC) &polygonToCells);
  R_RegisterCCallable("h3lib", "cellsToLinkedMultiPolygon",         (DL_FUNC) &cellsToLinkedMultiPolygon);
  R_RegisterCCallable("h3lib", "destroyLinkedMultiPolygon",         (DL_FUNC) &destroyLinkedMultiPolygon);
  R_RegisterCCallable("h3lib", "degsToRads",         (DL_FUNC) &degsToRads);
  R_RegisterCCallable("h3lib", "radsToDegs",         (DL_FUNC) &radsToDegs);
  R_RegisterCCallable("h3lib", "greatCircleDistanceRads",         (DL_FUNC) &greatCircleDistanceRads);
  R_RegisterCCallable("h3lib", "greatCircleDistanceKm",         (DL_FUNC) &greatCircleDistanceKm);
  R_RegisterCCallable("h3lib", "greatCircleDistanceM",         (DL_FUNC) &greatCircleDistanceM);
  R_RegisterCCallable("h3lib", "getHexagonAreaAvgKm2",         (DL_FUNC) &getHexagonAreaAvgKm2);
  R_RegisterCCallable("h3lib", "getHexagonAreaAvgM2",         (DL_FUNC) &getHexagonAreaAvgM2);
  R_RegisterCCallable("h3lib", "cellAreaRads2",         (DL_FUNC) &cellAreaRads2);
  R_RegisterCCallable("h3lib", "cellAreaKm2",         (DL_FUNC) &cellAreaKm2);
  R_RegisterCCallable("h3lib", "cellAreaM2",         (DL_FUNC) &cellAreaM2);
  R_RegisterCCallable("h3lib", "getHexagonEdgeLengthAvgKm",         (DL_FUNC) &getHexagonEdgeLengthAvgKm);
  R_RegisterCCallable("h3lib", "getHexagonEdgeLengthAvgM",         (DL_FUNC) &getHexagonEdgeLengthAvgM);
  R_RegisterCCallable("h3lib", "edgeLengthRads",         (DL_FUNC) &edgeLengthRads);
  R_RegisterCCallable("h3lib", "edgeLengthKm",         (DL_FUNC) &edgeLengthKm);
  R_RegisterCCallable("h3lib", "edgeLengthM",         (DL_FUNC) &edgeLengthM);
  R_RegisterCCallable("h3lib", "getNumCells",         (DL_FUNC) &getNumCells);
  R_RegisterCCallable("h3lib", "res0CellCount",         (DL_FUNC) &res0CellCount);
  R_RegisterCCallable("h3lib", "getRes0Cells",         (DL_FUNC) &getRes0Cells);
  R_RegisterCCallable("h3lib", "pentagonCount",         (DL_FUNC) &pentagonCount);
  R_RegisterCCallable("h3lib", "getPentagons",         (DL_FUNC) &getPentagons);
  R_RegisterCCallable("h3lib", "getResolution",         (DL_FUNC) &getResolution);
  R_RegisterCCallable("h3lib", "getBaseCellNumber",         (DL_FUNC) &getBaseCellNumber);
  R_RegisterCCallable("h3lib", "stringToH3",         (DL_FUNC) &stringToH3);
  //R_RegisterCCallable("h3lib", "h3ToString",         (DL_FUNC) &h3ToString);
  R_RegisterCCallable("h3lib", "isValidCell",         (DL_FUNC) &isValidCell);
  R_RegisterCCallable("h3lib", "cellToParent",         (DL_FUNC) &cellToParent);
  R_RegisterCCallable("h3lib", "cellToChildrenSize",         (DL_FUNC) &cellToChildrenSize);
  R_RegisterCCallable("h3lib", "cellToChildren",         (DL_FUNC) &cellToChildren);
  R_RegisterCCallable("h3lib", "cellToCenterChild",         (DL_FUNC) &cellToCenterChild);
  R_RegisterCCallable("h3lib", "cellToChildPos",         (DL_FUNC) &cellToChildPos);
  R_RegisterCCallable("h3lib", "childPosToCell",         (DL_FUNC) &childPosToCell);
  R_RegisterCCallable("h3lib", "compactCells",         (DL_FUNC) &compactCells);
  R_RegisterCCallable("h3lib", "uncompactCellsSize",         (DL_FUNC) &uncompactCellsSize);
  R_RegisterCCallable("h3lib", "uncompactCells",         (DL_FUNC) &uncompactCells);
  R_RegisterCCallable("h3lib", "isResClassIII",         (DL_FUNC) &isResClassIII);
  R_RegisterCCallable("h3lib", "isPentagon",         (DL_FUNC) &isPentagon);
  R_RegisterCCallable("h3lib", "maxFaceCount",         (DL_FUNC) &maxFaceCount);
  R_RegisterCCallable("h3lib", "getIcosahedronFaces",         (DL_FUNC) &getIcosahedronFaces);
  R_RegisterCCallable("h3lib", "areNeighborCells",         (DL_FUNC) &areNeighborCells);
  R_RegisterCCallable("h3lib", "cellsToDirectedEdge",         (DL_FUNC) &cellsToDirectedEdge);
  R_RegisterCCallable("h3lib", "isValidDirectedEdge",         (DL_FUNC) &isValidDirectedEdge);
  R_RegisterCCallable("h3lib", "getDirectedEdgeOrigin",         (DL_FUNC) &getDirectedEdgeOrigin);
  R_RegisterCCallable("h3lib", "getDirectedEdgeDestination",         (DL_FUNC) &getDirectedEdgeDestination);
  R_RegisterCCallable("h3lib", "directedEdgeToCells",         (DL_FUNC) &directedEdgeToCells);
  R_RegisterCCallable("h3lib", "originToDirectedEdges",         (DL_FUNC) &originToDirectedEdges);
  R_RegisterCCallable("h3lib", "directedEdgeToBoundary",         (DL_FUNC) &directedEdgeToBoundary);
  R_RegisterCCallable("h3lib", "cellToVertex",         (DL_FUNC) &cellToVertex);
  R_RegisterCCallable("h3lib", "cellToVertexes",         (DL_FUNC) &cellToVertexes);
  R_RegisterCCallable("h3lib", "vertexToLatLng",         (DL_FUNC) &vertexToLatLng);
  R_RegisterCCallable("h3lib", "isValidVertex",         (DL_FUNC) &isValidVertex);
  R_RegisterCCallable("h3lib", "gridDistance",         (DL_FUNC) &gridDistance);
  R_RegisterCCallable("h3lib", "gridPathCellsSize",         (DL_FUNC) &gridPathCellsSize);
  R_RegisterCCallable("h3lib", "gridPathCells",         (DL_FUNC) &gridPathCells);
  R_RegisterCCallable("h3lib", "cellToLocalIj",         (DL_FUNC) &cellToLocalIj);
  R_RegisterCCallable("h3lib", "localIjToCell",         (DL_FUNC) &localIjToCell);

  // Non-API
  R_RegisterCCallable("h3lib", "directionForNeighbor",        (DL_FUNC) &directionForNeighbor);
  R_RegisterCCallable("h3lib", "_geoToClosestFace",           (DL_FUNC) &_geoToClosestFace);

  R_forceSymbols(info, TRUE);  // controls visibility

}

void R_unload_h3lib(DllInfo *info)
{
  // TODO:
  /* Release Resources */
}
