# Clean the build directory
rm -rf build

# Create a new build directory and navigate into it
mkdir build
cd build

# Run CMake and build the project
cmake ..
cmake --build .

# Run the game
./MyGame

# Return to root dir
cd ..