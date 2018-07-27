cmake_minimum_required (VERSION 2.6)
project (block_chain)
SET(ROOT ${CMAKE_CURRENT_SOURCE_DIR}) 
SET(OUTPUT block-chain-binary)

# The version number.
set (Ctest_VERSION_MAJOR 1)
set (Ctest_VERSION_MINOR 0)

SET(CMAKE_CXX_COMPILER "g++") 
SET(CMAKE_CXX_FLAGS "-g -O2 -D_GNU_SOURCE -D__STDC_LIMIT_MACROS -DVERSION=\\\"1-1-35\\\" -W -Wall -finline-functions -fPIC -Wswitch -Wformat -Wreorder -Wno-conversion -Wpointer-arith -Wno-invalid-offsetof -Wno-deprecated -Wno-unused-value -Wno-unused-parameter")

if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 4.0) 
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-local-typedefs") 
endif()

# Include path
INCLUDE_DIRECTORIES(
    ${ROOT}/
    ${ROOT}/src
    ${ROOT}/src/mongoose
    ${ROOT}/src/common
    ${ROOT}/src/chain
    ${ROOT}/src/server
    ${ROOT}/src/connector
    ${ROOT}/dep/glog/include
)

# Lib path
LINK_DIRECTORIES(
    ${ROOT}/dep/glog/lib
)

# Libraries
SET (DEP_LIBRARY
    glog.a
)

# Executable
FILE(GLOB_RECURSE ServerCppFiles src/*.cpp src/*.c)

ADD_LIBRARY(bbc ${ServerCppFiles})

ADD_EXECUTABLE(chainer "src/main.cpp")

target_link_libraries(chainer "-Xlinker" "-(" bbc ${DEP_LIBRARY} "-Xlinker" "-)")
