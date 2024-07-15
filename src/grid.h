#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "graphics.h"
#include "spritesheet.h"

class Grid {
public:
    Grid(const std::string& filePath);
    bool loadGrid();
    void drawGrid(Graphics& graphics, SpriteSheet& spriteSheet);

private:
    std::string filePath;
    std::vector<std::vector<int>> gridData;

    TextureType getTextureType(int value);
};

#endif // GRID_H
