#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <SDL2/SDL.h>
#include "graphics.h"
#include "spritesheet.h"
#include "constants.h"

class Grid {
public:
    Grid(const std::string& filePath, Graphics& graphics, SpriteSheet& spriteSheet);
    bool loadGrid();
    void drawGrid();

private:
    std::string filePath;
    std::vector<std::vector<int>> gridData;

    Graphics& graphics;
    SpriteSheet& spriteSheet;

    TextureType getTextureType(int value);
};

#endif // GRID_H
