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

include(FindPkgConfig)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)
pkg_check_modules(SDL2_Image REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_Ttf REQUIRED IMPORTED_TARGET SDL2_ttf)

# Include directories (if you have header files in a separate directory)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_Mixer_INCLUDE_DIRS} ${SDL2_Image_INCLUDE_DIRS} ${SDL2_Ttf_INCLUDE_DIRS})  # Include SDL2 and SDL2_mixer headers

# Add executable with all source files
add_executable(OpenBlank
    BulletHole.cpp
    LTexture.cpp
    LTarget.cpp
    OpenBlank.cpp
    Sound.cpp
    SDL.cpp
    Media.cpp
    Movement.cpp
    Player.cpp
    Hud.cpp
    Game.cpp
    Event.cpp
    Detect.cpp
    Round.cpp
    Title.cpp
    Rounds/Fountain.cpp
    Rounds/Telephone.cpp
    Rounds/Simon.cpp
    Rounds/Speller.cpp
    Rounds/ShootNumbers.cpp
    Rounds/Asteroids.cpp
    Rounds/QuickDraw.cpp
    Rounds/Burger.cpp
    Rounds/Saloon.cpp
    Rounds/Doctor.cpp
    Rounds/WheresTuxy.cpp
    Rounds/Bride.cpp
    Background.cpp
)

# Specify libraries to link
target_link_libraries(OpenBlank ${SDL2_LIBRARIES} PkgConfig::SDL2_Mixer PkgConfig::SDL2_Image PkgConfig::SDL2_Ttf)

file(COPY ${CMAKE_BINARY_DIR}/../data DESTINATION ${CMAKE_BINARY_DIR}/)
