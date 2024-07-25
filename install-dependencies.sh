#!/bin/bash

# For development

# Install cmake
brew cmake;

# Install IWYU
brew include-what-you-use;

# For the product

# Update Homebrew
brew update

# Install SDL2
brew install sdl2

# Install SDL2_image
brew install sdl2_image

# Install SDL2_ttf
brew install sdl2_ttf

# Install SDL2_mixer
brew install sdl2_mixer

echo "All dependencies have been installed."
