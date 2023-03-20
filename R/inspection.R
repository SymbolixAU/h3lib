
#' Get Resolution
#'
#' Returns the resolution of the index.
#'
#' @inheritParams cellToLatLng
#'
#' @examples
#'
#' getResolution(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @return a vector the same length as `cell` giving the resolution of each index
#'
#' @export
getResolution <- function(cell) {
  .Call(h3rGetResolution, cell)
}
