#' @useDynLib h3lib, .registration = TRUE
NULL


#' Test
#'
#' @export
test <- function() {
  .Call(h3lib_latLngToCell, 1, 1, 1L)
}
