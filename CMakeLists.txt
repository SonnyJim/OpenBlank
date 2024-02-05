# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(OpenBlank)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Find the SDL2 package
find_package(SDL2 REQUIRED)

# Include directories (if you have header files in a separate directory)
include_directories(${SDL2_INCLUDE_DIRS})  # Include SDL2 headers
include_directories(.)

message(${SDL2_INCLUDE_DIRS})

# Add executable with all source files
add_executable(OpenBlank 
    LTarget.cpp
    LTexture.cpp
    OpenBlank.cpp
    Sound.cpp
)

# Specify libraries to link
target_link_libraries(OpenBlank ${SDL2_LIBRARIES})
