#ifndef GRID_H
#define GRID_H

#include <string>         // for string, basic_string
#include <vector>         // for vector
#include "spritesheet.h"  // for TextureType
class Graphics;

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
