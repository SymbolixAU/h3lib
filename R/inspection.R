
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


#' Get Base Cell Number
#'
#' Returns the base cell number of the index
#'
#' @inheritParams cellToLatLng
#'
#' @examples
#'
#' getBaseCellNumber(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @return a vector the same length as `cell` giving the base cell number of each index
#'
#' @export
getBaseCellNumber <- function(cell) {
  .Call(h3rGetBaseCellNumber, cell)
}

## TODO:
# h3ToString
# stringToH3


#' Is Valid Cell
#'
#' Returns non-zero if this is a valid H3 cell index
#'
#' @inheritParams cellToLatLng
#'
#' @examples
#'
#' isValidCell(cell = c("8cbe63562a54bff","8cbe635631103ff", "abc", "3"))
#'
#' @return a vector the same length as `cell` giving the validity of the cell
#'
#' @export
isValidCell <- function(cell) {
  .Call(h3rIsValidCell, cell)
}


#' Is Res Class III
#'
#' Returns non-zero if this index has a resolution with Class III orientation.
#'
#' @inheritParams cellToLatLng
#'
#' @examples
#'
#' isResClassIII(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @return a vector the same length as `cell` indicating if the cell is Class II
#'
#' @export
isResClassIII <- function(cell) {
  .Call(h3rIsResClassIII, cell)
}


#' Is Pentagon
#'
#' Returns non-zero if this index represents a pentagonal cell.
#'
#' @inheritParams cellToLatLng
#'
#' @examples
#'
#' isPentagon(cell = c("8cbe63562a54bff","8cbe635631103ff"))
#'
#' @return a vector the same length as `cell` indicating if the cell is Class II
#'
#' @export
isPentagon <- function(cell) {
  .Call(h3rIsPentagon, cell)
}

## TODO:
# getIcosahedronFaces
# maxFaceCount

