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
#' latLngToCell(
#'   lat = c(-37.820197, -37.818476)
#'   , lng = c(144.983324, 144.967354)
#'   , resolution = 12L
#'   )
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
#' cellToLatLng(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @export
cellToLatLng <- function(cell) {
  .Call(h3rCellToLatLng, cell)
}

#' Cell To Boundary
#'
#' @examples
#'
#' cellToBoundary(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @export
cellToBoundary <- function(cell) {
  .Call(h3rCellToBoundary, cell)
}

#' Great Circle Distance In Radians
#'
#' @examples
#'
#' greatCirlceDistanceRads(
#'   aLats = c(-37.820197)
#'   , aLons = c(144.983324)
#'   , bLats = c(-37.818476)
#'   , bLons = c(144.967354)
#' )
#'
#' @export
greatCirlceDistanceRads <- function(aLats, aLons, bLats, bLons) {
  .Call(h3rGreatCircleDistanceRads, aLats, aLons, bLats, bLons)
}


#' Great Circle Distance In Meters
#'
#' @examples
#'
#' greatCirlceDistanceM(
#'   aLats = c(-37.820197)
#'   , aLons = c(144.983324)
#'   , bLats = c(-37.818476)
#'   , bLons = c(144.967354)
#' )
#'
#' @export
greatCirlceDistanceM <- function(aLats, aLons, bLats, bLons) {
  .Call(h3rGreatCircleDistanceM, aLats, aLons, bLats, bLons)
}

#' Great Circle Distance In Kilometers
#'
#' @examples
#'
#' greatCirlceDistanceKm(
#'   aLats = c(-37.820197)
#'   , aLons = c(144.983324)
#'   , bLats = c(-37.818476)
#'   , bLons = c(144.967354)
#' )
#'
#' @export
greatCirlceDistanceKm <- function(aLats, aLons, bLats, bLons) {
  .Call(h3rGreatCircleDistanceKm, aLats, aLons, bLats, bLons)
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





