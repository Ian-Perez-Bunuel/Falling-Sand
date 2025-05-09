#pragma once

#include "../include/Pixel.h"

class World
{
public:
    World();

    void update();
    void draw();

private:
    float pixelSize = 5;
    int worldWidth = 140;
    int worldHeight = 140;

    std::vector<std::shared_ptr<Pixel>> worldPixels;

    // Spawning
    std::shared_ptr<Pixel> getPixelUnderMouse();
    void spawnOnMouse();

    // Grid
    void drawGrid();

    // Debugging
    bool debugMode = false;
};