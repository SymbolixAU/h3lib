#' @useDynLib "h3r", .registration = TRUE
NULL


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





