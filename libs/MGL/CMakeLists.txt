# Set cmake minimum version
cmake_minimum_required(VERSION 3.15)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Declare project
project(MGL VERSION 0.0.01 DESCRIPTION "For now the name is MGL (=My Game Library)")

# Set output directory for the static library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add include directory
include_directories(include)

# Add source files from ./src
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Set the output directory for the static library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

# Create a static library
add_library(MGL STATIC ${SOURCES})

# Specify the output name of the library
set_target_properties(MGL PROPERTIES OUTPUT_NAME "MGL")