cmake_minimum_required(VERSION 3.9)

project(libed25519
    VERSION 0.1.0
    DESCRIPTION "ED25519 Implemetation using BLAKE3."
    LANGUAGES C)

set(BUILD_SHARED_LIBS ON)

add_subdirectory(lib/BLAKE3)

file(GLOB_RECURSE SOURCES src/*.c)

add_library(ed25519 SHARED ${SOURCES})
add_library(ED25519::ED25519 ALIAS ed25519)

target_include_directories(ed25519 PUBLIC ./src ./lib/BLAKE3/src)
target_link_libraries(ed25519 PUBLIC BLAKE3::blake3)