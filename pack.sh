set -euo pipefail 

#!/bin/bash 
CC="g++"
FILE_EXTENSION="cc"
SRC="src"
OBJ="obj"
LIBDIRS=()
LIBS=("SDL2")
FRAMEWORKS=()
INC=("include")
CFLAGS="-std=c++20 -Wall -Wextra"
LFLAGS=""
BUILD_DIR="build"
EXECUTABLE="app"

function add_cflags() {
    for dep in "${@:2}"; do
        CFLAGS+=" -${1}${dep}"
    done
}

function add_lflags() {
    for dep in "${@:2}"; do
        LFLAGS+=" -${1}${dep}"
    done
}

function check_dir() {
    if [[ ! -d ${1} ]]; then
        printf "ERROR \t Directory ${1} does not exist.\n"
        exit 1
    fi

    if [[ -z $(ls -A ${1}) ]]; then
        printf "ERROR \t Directory ${1} is empty.\n"
        exit 1
    fi
}

function copy_dir() {
     if [[ ! -d ${1} ]]; then
        printf "ERROR \t Source directory ${1} does not exist.\n"
    fi

    if [[ ! -d ${2} ]]; then
        printf "ERROR \t Destination directory ${2} does not exist.\n"
    fi

    cp -r ${1} "${2}/${1}"
}

function make_dir() {
    mkdir -p ${1}
}

function clean() {
    rm -rf ${BUILD_DIR}
    if [[ -f ${EXECUTABLE} ]]; then
        rm ${EXECUTABLE}
    fi
}

function make_objects() {
    for src_file in ${1}; do
        local obj_file=$(echo ${src_file//$SRC/$OBJ} | sed "s/\.${FILE_EXTENSION}/\.o/")
        ${CC} ${CFLAGS} -c ${src_file} -o ${obj_file}
    done
}

function link_objects() {
    # Make sure lflags come after objects are linked.
    ${CC} ${1} -o ${EXECUTABLE} ${LFLAGS}
}

function build() {
    printf "INFO \t Checking directories...\n"
    check_dir ${SRC}
    # check_dir ${INC}

    printf "INFO \t Cleaning...\n"
    clean

    printf "INFO \t Creating build directory...\n"
    make_dir ${BUILD_DIR}
    make_dir "${BUILD_DIR}/${OBJ}"
    copy_dir ${SRC} ${BUILD_DIR}
    copy_dir ${INC} ${BUILD_DIR} 

    cd ${BUILD_DIR}
    if [[ "${#INC[@]}" != 0 ]]; then
        add_cflags "I" "${INC[@]}"
    fi
    if [[ "${#LIBDIRS[@]}" != 0 ]]; then
        add_lflags "L" "${LIBDIRS[@]}"
    fi
    if [[ "${#LIBS[@]}" != 0 ]]; then
        add_lflags "l" "${LIBS[@]}"
    fi

    SOURCES=$(find ${SRC} -name "*.${FILE_EXTENSION}" -type f)
    OBJECTS=$(echo ${SOURCES//$SRC/$OBJ} | sed "s/\.${FILE_EXTENSION}/\.o/g")

    printf "INFO \t Creating object files...\n"
    make_objects "${SOURCES}"

    printf "INFO \t Linking objects...\n"
    link_objects "${OBJECTS}"

    printf "INFO \t Copying executable to project directory...\n"
    cp ${EXECUTABLE} ../

    printf "INFO \t Successfully built.\n"

    cd ".."
}

function run() {
    build

    ./${EXECUTABLE}

    printf "INFO \t Executable ran successfully.\n"
    clean
}

if [[ ${1} == "build" ]]; then
    build
elif [[ ${1} == "run" ]]; then
    run
elif [[ ${1} == "clean" ]]; then 
    clean
else
    printf "ERROR \t Invalid argument.\n"
    exit 1
fi 
