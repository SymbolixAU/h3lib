
#' Degrees To Rads
#'
#' Converts Degrees to Radians
#'
#' @param deg vector of degrees
#'
#' @examples
#'
#' degsToRads(deg = seq(0, 360, by = 15))
#'
#'
#' @export
degsToRads <- function(deg) {
  .Call(h3rDegsToRads, deg)
}

#' Rads to Degrees
#'
#' Converts Radians to Degrees
#'
#' @param rad vector of radians
#'
#' @examples
#' radsToDegs(rad = seq(0, 2 * pi, by = (pi / 12) ) )
#'
#' @export
radsToDegs <- function(rad) {
  .Call(h3rRadsToDegs, rad)
}

#' Exact area of specific cell in square radians.
#'
#' @param cell vector of H3 cells
#'
#' @return the exact area of specific cell in square radians.
#'
#' @examples
#'
#' cellAreaRads2(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @export
cellAreaRads2 <- function(cell) {
  .Call(h3rCellAreaRads2, cell)
}

#' Exact area of specific cell in square meters.
#'
#' @param cell vector of H3 cells
#'
#' @return the exact area of specific cell in square meters.
#'
#' @examples
#'
#' cellAreaM2(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @export
cellAreaM2 <- function(cell) {
  .Call(h3rCellAreaM2, cell)
}

#' Exact area of specific cell in square kilometers.
#'
#' @param cell vector of H3 cells
#'
#' @return the exact area of specific cell in square kilometers.
#'
#' @examples
#'
#' cellAreaKm2(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @export
cellAreaKm2 <- function(cell) {
  .Call(h3rCellAreaKm2, cell)
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



#' Direction For Neighbor
#'
#'
#' @export
directionForNeighbor <- function(origin, destination) {
  .Call(h3rDirectionForNeighbour, origin, destination)
}





