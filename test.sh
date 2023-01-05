set -xe pipefail

INC=("include" "GLEW")
CFLAGS="-std=c++20 -Wall -Wextra"

function add_cflags()
{
    echo ${1}
    echo ${@:2}
    for dep in "${@:2}"; do
        CFLAGS+=" -${1}${dep}"
    done
}

# Append include directories to CFLAGS.
# add_flags "I" "${CFLAGS}" "${INC[@]}"
# Add the -I to all the include directories.
# for dep in "${INC[@]}"; do
#     CFLAGS+=" -I${dep}"
# done
add_cflags "I"  "${INC[@]}"

echo ${CFLAGS}