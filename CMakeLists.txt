cmake_minimum_required(VERSION 3.14)
project(BeesAlgo)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master)

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(Headers Bee/Bee.h Hive/Hive.h Utils.h)
set(Sources main.cpp Bee/Bee.cpp Hive/Hive.cpp Function.h)

add_executable(BeesAlgo ${Headers} ${Sources})
target_link_libraries(BeesAlgo PUBLIC matplot)