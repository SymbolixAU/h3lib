#' @useDynLib "h3r", .registration = TRUE
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
  .Call(h3rLatLngToCell, lat, lng, resolution)
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
  .Call(h3rCellToLatLng, cell)
}

#' Cell To Boundary
#'
#' @examples
#'
#' cellToBoundary(cell = c("8cbe44a96a9c1ff","8c3752c716b43ff"))
#'
#' @export
cellToBoundary <- function(cell) {
  .Call(h3rCellToBoundary, cell)
}

#'
#' #' H3 To String
#' #'
#' #' @examples
#' #'
#' #'
#' #'
#' #' @export
#' h3ToString <- function(h) {
#'   .Call(h3rH3ToString, h)
#' }
#'
#'
#' #' String To H3
#' #'
#' #' @examples
#' #'
#' #' stringToH3(c("8cbe44a96a9c1ff"))
#' #'
#' #' @export
#' stringToH3 <- function(h) {
#'   .Call(h3rStringToH3, h)
#' }


#' Direction For Neighbor
#'
#'
#' @export
directionForNeighbor <- function(origin, destination) {
  .Call(h3rDirectionForNeighbour, origin, destination)
}





