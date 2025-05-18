# Project name
project(2D_team_fighter)

# Set cmake minimum version
cmake_minimum_required(VERSION 3.15)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files from ./src
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Remove main_wasm.cpp from the list.
list(REMOVE_ITEM SOURCES "${CMAKE_SOURCE_DIR}/src/main_wasm.cpp")

# Create the executable target
add_executable(${PROJECT_NAME} ${SOURCES})

# Link MGL library (static)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs/MGL/lib/libMGL.a)

# Include libraries in ./libs
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs)

# Add CMake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/sdl2")

###################################################################################################################
# Make sure SDL2 is linked after MGL!!! Library providing symbols must appear after a library that depends on it. #
###################################################################################################################

# Add SDL2 library
find_package(SDL2 REQUIRED)

# Platform-specific configurations
if (WIN32)
    # Additional configuration for Windows
    ### NOT YET IMPLEMENTED ###
elseif (UNIX)
    # Link SDL2 libraries and include directories
    target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} pthread)
    target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS})
endif()