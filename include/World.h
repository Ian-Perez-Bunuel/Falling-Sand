#pragma once
#include "raylib.h"
#include "stdio.h"

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
    PixelType selectedType = PixelType::SAND;


    // Grid
    void drawGrid();

    bool debugMode = false;
};