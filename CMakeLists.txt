cmake_minimum_required(VERSION 3.15)
project(BeesAlgo)

set (CMAKE_CXX_STANDARD 17)

include(FetchContent)

FetchContent_Declare(matplotplusplus
        GIT_REPOSITORY https://github.com/alandefreitas/matplotplusplus
        GIT_TAG origin/master) # or whatever tag you want

FetchContent_GetProperties(matplotplusplus)
if(NOT matplotplusplus_POPULATED)
    FetchContent_Populate(matplotplusplus)
    add_subdirectory(${matplotplusplus_SOURCE_DIR} ${matplotplusplus_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

set(Headers Bee.h Hive.h SphericalBee.h Utils.h RastriginBee.h RosenbrokBee.h )
set(Sources main.cpp Bee.cpp Hive.cpp SphericalBee.cpp  RastriginBee.cpp RosenbrokBee.cpp LeviBee.cpp LeviBee.h)

add_executable(BeesAlgo ${Headers} ${Sources})
target_link_libraries(BeesAlgo PUBLIC matplot)