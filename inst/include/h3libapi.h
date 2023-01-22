//
// #ifndef R_H3LIB_API_H
// #define R_H3LIB_API_H
//
// #include <R.h>
// // #include <RInternals.h>
// #include <Rconfig.h>
// #include <R_ext/Rdynload.h>
//
// #ifdef HAVE_VISIBILITY_ATTRIBUTE
// # define attribute_hidden __attribute__ ((visibility ("hidden")))
// #else
// # define attribute_hidden
// #endif
//
// #ifdef __cplusplus
// extern "C" {
// #endif
//
//
// // SEXP attribute_hidden h3libLatLngToCell(SEXP lat, SEXP lon, SEXP res) {
// //   static SEXP(*fun)(SEXP, SEXP, SEXP) =
// //     (SEXP(*)(SEXP, SEXP, SEXP)) R_GetCCallable("h3lib", "CLatLngToCell");
// //   return fun(lat, lon, res);
// // }
//
//
// #ifdef __cplusplus
// }
//
// /*
// namespace h3lib {
//   inline SEXP latLngToCell(SEXP lat, SEXP lon, SEXP res) {
// //    Rcpp::IntegerVector iv(1);
// //    return iv;
//     return h3libLatLngToCell(lat, lon, res);
//   }
// }
// */
//
// #endif
//
// #endif // R_H3LIB_API_H
