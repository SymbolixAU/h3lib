
#ifndef R_H3R_API_H
#define R_H3R_API_H

#include <R.h>
#include <Rinternals.h>
#include <Rconfig.h>
#include <R_ext/Rdynload.h>

#ifdef HAVE_VISIBILITY_ATTRIBUTE
# define attribute_hidden __attribute__ ((visibility ("hidden")))
#else
# define attribute_hidden
#endif

#ifdef __cplusplus
extern "C" {
#endif


inline SEXP attribute_hidden h3r_latLngToCell(SEXP lat, SEXP lon, SEXP res) {
  SEXP(*fun)(SEXP, SEXP, SEXP) =
    (SEXP(*)(SEXP, SEXP, SEXP)) R_GetCCallable("h3r", "h3r_latLngToCell");
  return fun(lat, lon, res);
}


#ifdef __cplusplus
}


namespace h3r {
  inline SEXP latLngToCell(SEXP lat, SEXP lon, SEXP res) {
    return h3LatLngToCell(lat, lon, res);
  }
}


#endif

#endif // R_H3R_API_H
