cmake_minimum_required(VERSION 3.10)

# Project name
project(GhostDriver)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler warning flags
set(WARN_FLAGS
    -Wall
    -Wextra
    -Werror
    -Wshadow
    -Wconversion
    -pedantic
    -pedantic-errors
    -Wformat=2
    -Wundef
    -Wredundant-decls
    -Wmissing-declarations
    -Wmissing-include-dirs
    -Wswitch-enum
)

# Apply warning flags
add_compile_options(${WARN_FLAGS})

# Manually set SDL2_image include and library directories
set(SDL2_IMAGE_INCLUDE_DIRS /opt/homebrew/include/)
set(SDL2_IMAGE_LIBRARIES /opt/homebrew/lib/libSDL2_image.dylib)

# Manually set SDL2_ttf include and library directories
set(SDL2_TTF_INCLUDE_DIRS /opt/homebrew/include/)
set(SDL2_TTF_LIBRARIES /opt/homebrew/lib/libSDL2_ttf.dylib)

# Manually set SDL2_ttf include and library directories
set(SDL2_MIXER_INCLUDE_DIRS /opt/homebrew/include/)
set(SDL2_MIXER_LIBRARIES /opt/homebrew/lib/libSDL2_mixer.dylib)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Debug messages
message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_image include dirs: ${SDL2_IMAGE_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf include dirs: ${SDL2_TTF_INCLUDE_DIRS}")
message(STATUS "SDL2_mixer include dirs: ${SDL2_MIXER_INCLUDE_DIRS}")

# Enable IWYU
set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "include-what-you-use;-Xiwyu;--mapping_file=../mappings.imp")

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
    src/title-screen.cpp
    src/user-interface.cpp
    src/sound.cpp
)

# Link SDL2, SDL2_image, SDL2_ttf, and SDL2_mixer
target_link_libraries(GhostDriver ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES})

# Explicitly add include directories
target_include_directories(GhostDriver PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})
