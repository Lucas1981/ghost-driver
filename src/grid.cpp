#include "grid.h"
#include <fstream>
#include <iostream>

Grid::Grid(const std::string& filePath, Graphics& graphics, SpriteSheet& spriteSheet)
    : filePath(filePath), graphics(graphics), spriteSheet(spriteSheet) {}

bool Grid::loadGrid() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open grid file: " << filePath << std::endl;
        return false;
    }

    gridData.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c >= '0' && c <= '9') {
                row.push_back(c - '0');
            }
        }
        gridData.push_back(row);
    }

    file.close();
    return true;
}

TextureType Grid::getTextureType(int value) {
    switch (value) {
        case 0: return TextureType::GRASS;
        case 1: return TextureType::PLAIN_ROAD;
        case 2: return TextureType::STRIPED_ROAD;
        default: return TextureType::GRASS;
    }
}

void Grid::drawGrid(Graphics& graphics, SpriteSheet& spriteSheet) {
    int tileSize = 64;
    for (size_t y = 0; y < gridData.size(); ++y) {
        for (size_t x = 0; x < gridData[y].size(); ++x) {
            TextureType textureType = getTextureType(gridData[y][x]);
            graphics.drawTexture(x * tileSize, y * tileSize, tileSize, spriteSheet.getTextureSlice(textureType));
        }
    }
}
