
#' Cell To Parent
#'
#' Provides the parent (coarser) index containing `cell`
#'
#' @inheritParams cellToLatLng
#' @param parentRes integer vector specifying the parent resolution for each `cell`
#'
#' @return vector of parent cells for each `cell`
#'
#' @examples
#'
#' cell <- "8cbe63562a54bff"
#' getResolution(cell = cell)
#'
#' ## The `parentRes` should be a lower value than the result of `getResolution()`
#' cellToParent(cell = rep(cell, 2), parentRes = c(11L, 10L))
#'
#'
#' @export
cellToParent <- function(cell, parentRes) {
  .Call(h3rCellToParent, cell, parentRes)
}

## TODO:
# cellToChildren
# cellToChildrenSize
# cellToCenterChild
# cellToChildPos
# compactCells
# uncompactCells
# uncompactCellsSize

