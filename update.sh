#!/bin/bash
repo_url="https://github.com/uber/h3.git"
repo_folder="h3"
compare_folder="src"
repo_src="src/h3lib"
input_file="$repo_folder/$repo_src/lib/h3api.h"
# output_file="$repo_folder/$repo_src/lib/init.c"
# output_file_2="h3libapi.h"
compare_file="inst/include/h3libapi.h"
api_differences="api_differences.h"

echo "Update from uber/h3? (y/n)"
read -r answer

case $answer in
    [Nn]* ) echo "Quitting..."; exit;;
    [Yy]* )
        git clone "$repo_url" "$repo_folder" || { echo "Error cloning repository"; exit 1; }
        mv $repo_folder/$repo_src/include/* $repo_folder/$repo_src/lib
        mv $repo_folder/$repo_src/lib/h3api.h.in $repo_folder/$repo_src/lib/h3api.h

        # # Build the init.c
        # echo -e "\nFunctions:"
        # functions=$(sed -n 's/^.*H3_EXPORT(\([^)]*\)).*$/\1/p' "$input_file" | grep -v '^name$')
        #
        # content="// #include \"h3api.h\"\n\n#include \"algos.h\" // directionForNeighbor\n\n#include <R.h>\n#include <Rconfig.h>\n#include <Rinternals.h>\n#include <R_ext/Rdynload.h>\n#include <R_ext/Visibility.h>\n\n\n/* Define .Call functions */\nstatic const R_CallMethodDef callMethods[] = {\n  {NULL,                NULL,                        0}\n};\n\nvoid attribute_visible R_init_h3lib(DllInfo *info)\n{\n  R_registerRoutines(info, NULL, callMethods, NULL, NULL);\n\n  R_useDynamicSymbols(info, FALSE);\n\n"
        # for func in $functions; do
        #     echo $func
        #     content+="\n  R_RegisterCCallable(\"h3lib\", \"$func\",         (DL_FUNC) &$func);"
        # done
        # content+="\n\n  // Non-API\n  R_RegisterCCallable(\"h3lib\", \"directionForNeighbor\",        (DL_FUNC) &directionForNeighbor);\n\n  R_forceSymbols(info, TRUE);  // controls visibility\n\n}\n\nvoid R_unload_h3lib(DllInfo *info)\n{\n  // TODO:\n  /* Release Resources */\n}"
        # echo -e "$content" > "$output_file"

        # Compare error code
        error_originial="typedef uint32_t H3Error;

typedef enum {
    E_SUCCESS = 0,  // Success (no error)
    E_FAILED =
        1,  // The operation failed but a more specific error is not available
    E_DOMAIN = 2,  // Argument was outside of acceptable range (when a more
                   // specific error code is not available)
    E_LATLNG_DOMAIN =
        3,  // Latitude or longitude arguments were outside of acceptable range
    E_RES_DOMAIN = 4,    // Resolution argument was outside of acceptable range
    E_CELL_INVALID = 5,  // \`H3Index\` cell argument was not valid
    E_DIR_EDGE_INVALID = 6,  // \`H3Index\` directed edge argument was not valid
    E_UNDIR_EDGE_INVALID =
        7,                 // \`H3Index\` undirected edge argument was not valid
    E_VERTEX_INVALID = 8,  // \`H3Index\` vertex argument was not valid
    E_PENTAGON = 9,  // Pentagon distortion was encountered which the algorithm
                     // could not handle it
    E_DUPLICATE_INPUT = 10,  // Duplicate input was encountered in the arguments
                             // and the algorithm could not handle it
    E_NOT_NEIGHBORS = 11,    // \`H3Index\` cell arguments were not neighbors
    E_RES_MISMATCH =
        12,  // \`H3Index\` cell arguments had incompatible resolutions
    E_MEMORY_ALLOC = 13,   // Necessary memory allocation failed
    E_MEMORY_BOUNDS = 14,  // Bounds of provided memory were not large enough
    E_OPTION_INVALID = 15  // Mode or flags argument was not valid.
} H3ErrorCodes;"

        extracted_text=$(sed -n '/typedef uint32_t H3Error;/,/H3ErrorCodes;/p' "$input_file")

        # Create temporary files for the extracted text and the target string
        extracted_file=$(mktemp)
        target_file=$(mktemp)

        # Save the extracted text and the target string into the temporary files
        echo "$extracted_text" > "$extracted_file"
        echo "$error_originial" > "$target_file"

        diff_output=$(diff "$target_file" "$extracted_file")

#         # Build the h3libapi.h
#         content="#ifndef R_H3LIB_API_H
# #define R_H3LIB_API_H
#
# #include <R.h>
# #include <Rinternals.h>
# #include <Rconfig.h>
# #include <R_ext/Rdynload.h>
#
# // #include \"h3api.h\" <-- can't include this as it' can't be found by linking packages
#
# #ifdef HAVE_VISIBILITY_ATTRIBUTE
# # define attribute_hidden __attribute__ ((visibility (\"hidden\")))
# #else
# # define attribute_hidden
# #endif
#
# #ifdef __cplusplus
# extern \"C\" {
# #endif
#
# typedef uint32_t H3Error;
#
# typedef enum {
#     /** H3 digit in center */
#     CENTER_DIGIT = 0,
#     /** H3 digit in k-axes direction */
#     K_AXES_DIGIT = 1,
#     /** H3 digit in j-axes direction */
#     J_AXES_DIGIT = 2,
#     /** H3 digit in j == k direction */
#     JK_AXES_DIGIT = J_AXES_DIGIT | K_AXES_DIGIT, /* 3 */
#     /** H3 digit in i-axes direction */
#     I_AXES_DIGIT = 4,
#     /** H3 digit in i == k direction */
#     IK_AXES_DIGIT = I_AXES_DIGIT | K_AXES_DIGIT, /* 5 */
#     /** H3 digit in i == j direction */
#     IJ_AXES_DIGIT = I_AXES_DIGIT | J_AXES_DIGIT, /* 6 */
#     /** H3 digit in the invalid direction */
#     INVALID_DIGIT = 7,
#     /** Valid digits will be less than this value. Same value as INVALID_DIGIT.
#     */
#     NUM_DIGITS = INVALID_DIGIT,
#     /** Child digit which is skipped for pentagons */
#     PENTAGON_SKIPPED_DIGIT = K_AXES_DIGIT /* 1 */
# } Direction;
#
# typedef uint64_t H3Index;
# "
#
#         structure=$(sed -n '/^#define MAX_CELL_BNDRY_VERTS 10/,/^\/\*\* @defgroup/p' $input_file | sed '$d')
#
#         content+="$structure"
#
#         input_combined=""
#         while IFS= read -r line; do
#           line=$(echo "$line" | tr -d '\r')
#           input_combined+="${line} "
#           if [[ $line =~ ";" ]]; then
#             input_combined+=$'\n'
#           fi
#         done < "$input_file"
#
#         # Remove excessive spaces
#         input_combined=$(echo "$input_combined" | tr -s ' ')
#
#         # Extract function names and arguments together
#         func_arg_pairs=$(echo "$input_combined" | sed -n 's/^.*DECLSPEC\s*\([^)]*\)\s*H3_EXPORT(\([^)]*\))\s*(\([^)]*\)).*$/\1|\2|\3/p')
#
#         # Convert to an array
#         IFS=$'\n' read -d '' -ra func_arg_arr <<< "$func_arg_pairs"
#
#         for pair in "${func_arg_arr[@]}"; do
#           # Split function name and arguments using '|' as the delimiter
#           IFS='|' read -ra func_arg <<< "$pair"
#           ret="${func_arg[0]}"
#           func="${func_arg[1]}"
#           arg="${func_arg[2]}"
#           arg="${arg//, /, }"
#
#           # Extract argument types and remove argument names
#           arg_types=$(echo "$arg" | sed -E 's/([a-zA-Z0-9_]+) \*([a-zA-Z0-9_]+)/\1* \2/g' | sed -E 's/([a-zA-Z0-9_*]+) ([a-zA-Z0-9_]+)(,|$)/\1\3/g')
#           arg_name=$(echo "$arg" | sed -E 's/([a-zA-Z0-9_]+) ([a-zA-Z0-9_]+) ([a-zA-Z0-9_*]+)/\2 \3/g'| sed -E 's/([a-zA-Z0-9_]+) ([a-zA-Z0-9_*]+)/\2/g'| sed -E 's/\*([a-zA-Z0-9_]+)/\1/g')
#
#           if [[ "$ret" == *"void"* ]]; then
#             content+="\n\ninline ${ret} ${func}( ${arg} ) {\n  ${ret}(*fun)( ${arg_types} ) =\n    (${ret}(*)( ${arg_types} )) R_GetCCallable(\"h3lib\",\"${func}\");\n  fun( ${arg_name} );\n}"
#           else
#             content+="\n\ninline ${ret} ${func}( ${arg} ) {\n  ${ret}(*fun)( ${arg_types} ) =\n    (${ret}(*)( ${arg_types} )) R_GetCCallable(\"h3lib\",\"${func}\");\n  return fun( ${arg_name} );\n}"
#           fi
#         done
#
#         content+="
#
#
# // Non-API
# inline Direction directionForNeighbor(H3Index origin, H3Index destination) {
# Direction(*fun)(H3Index, H3Index) =
#     (Direction(*)(H3Index, H3Index)) R_GetCCallable(\"h3lib\", \"directionForNeighbor\");
# return fun(origin, destination);
# }
#
# #ifdef __cplusplus
# }
#
#
# // namespace h3lib {
# //
# // }
#
#
# #endif  // __cplusplus
#
# #endif // R_H3LIB_API_H"

        # echo -e "$content" > "$repo_folder/$output_file_2"


        echo -e "\nDifferences:"
        diff -r --exclude='*.o' "${repo_folder}/${repo_src}/lib" "$compare_folder/"
        # diff "$repo_folder/$output_file_2" "$compare_file"

        # Display the difference in H3Error
        if [[ -z "$diff_output" ]]; then
          echo "No changes to H3Error"
        else
          echo "H3Error has been changed, please update it and the script manually"
          echo "Difference:"
          echo "$diff_output"
        fi

        echo -e "\nInstall the update? (y/n)"
        read -r answer
        case $answer in
            [Nn]* )
                rm -rf $repo_folder
                echo "Removing files and quitting..."; exit;;
            [Yy]* )
                rm -rf $compare_folder
                mkdir $compare_folder
                mv $repo_folder/$repo_src/lib/* $compare_folder/
                # mv $repo_folder/$output_file_2 $compare_file
                rm -rf $repo_folder
                echo "Finished update"
            ;;
            * ) echo "Invalid input";;
        esac
    ;;
    * ) echo "Invalid input";;
esac
