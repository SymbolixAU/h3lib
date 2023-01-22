#' @useDynLib "h3lib" , .registration = TRUE
NULL

#

#' lat lng to cell
#'
#' @param lat latitude
#' @param lng longitude
#' @param resolution cell resolution
#'
#' @examples
#'
#' latLngToCell(lat = c(-37, 37), lng = c(145, -145), resolution = 12L)
#'
#' @export
latLngToCell <- function(lat, lng, resolution) {
  .Call(h3libLatLngToCell, lat, lng, resolution)
}

#' Cell To Lat Lon
#'
#'
#' @examples
#'
#' cellToLatLng(cell = c("8cbe44a96a9c1ff","8c3752c716b43ff"))
#'
#' @export
cellToLatLng <- function(cell) {
  .Call(h3libCellToLatLng, cell)
}
