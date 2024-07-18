cmake_minimum_required(VERSION 3.10)

# Project name
project(MyGame)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Manually set SDL2_image include and library directories
set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include/)
set(SDL2_IMAGE_LIBRARIES /opt/homebrew/lib/libSDL2_image.dylib)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Debug messages
message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_image include dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")

# Add the executable
add_executable(GhostDriver 
    src/main.cpp 
    src/game-loop.cpp 
    src/graphics.cpp 
    src/clock.cpp 
    src/spritesheet.cpp 
    src/grid.cpp 
    src/input.cpp 
    src/player.cpp
    src/opponent.cpp
    src/agent.cpp
    src/collision.cpp
    src/state.cpp
    src/play.cpp
)

# Link SDL2 and SDL2_image
target_link_libraries(GhostDriver ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

# Explicitly add include directories
target_include_directories(GhostDriver PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
