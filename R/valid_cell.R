
#' Is Valid
#'
#' @examples
#'
#' is_valid("8cbe63562a54bff")
#'
#' @export
is_valid_cell <- function(cell) {
  .Call(is_valid, cell)
}
