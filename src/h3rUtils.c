
#include "h3rUtils.h"

void sexpToLatLng(LatLng *latLng, SEXP lat, SEXP lon, R_xlen_t idx) {
  latLng->lat = degsToRads(REAL(lat)[idx]);
  latLng->lng = degsToRads(REAL(lon)[idx]);
}

H3Index sexpStringToH3(SEXP h3, R_xlen_t idx) {
  H3Index index;
  stringToH3(CHAR(STRING_ELT(h3, idx)), &index);
  return index;
}

void latLngToSexp(LatLng *latLng, SEXP lats, SEXP lons, R_xlen_t idx) {
  double lat = radsToDegs(latLng->lat);
  double lon = radsToDegs(latLng->lng);

  SET_REAL_ELT(lats, idx, lat);
  SET_REAL_ELT(lons, idx, lon);
}

SEXP latLngList(SEXP lats, SEXP lons) {
  const char *names[] = {"lat","lng",""};
  SEXP res = PROTECT(mkNamed(VECSXP, names));

  SET_VECTOR_ELT(res, 0, lats);
  SET_VECTOR_ELT(res, 1, lons);
  UNPROTECT(1);
  return res;
}


SEXP cellBoundaryToList(CellBoundary *cb) {
   SEXP lats = PROTECT(Rf_allocVector(REALSXP, cb->numVerts));
   SEXP lons = PROTECT(Rf_allocVector(REALSXP, cb->numVerts));
   for( int i = 0; i < cb->numVerts; i++) {
     SET_REAL_ELT(lats, i, radsToDegs(cb->verts[i].lat));
     SET_REAL_ELT(lons, i, radsToDegs(cb->verts[i].lng));
   }
   UNPROTECT(2);
   return latLngList(lats, lons);
}
