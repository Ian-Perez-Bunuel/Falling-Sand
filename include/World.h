#pragma once

#include "../include/Pixel.h"
#include <math.h>


class World
{
public:
    void init();
    void update();
    void draw();

private:
    const int PIXEL_SIZE = 5;
    void calcWorldDimensions();
    int worldWidth;
    int worldHeight;

    std::vector<std::shared_ptr<Pixel>> worldPixels;

    // Spawning
    std::shared_ptr<Pixel> getPixelUnderMouse();
    void spawnOnMouse();

    // Areas
    static const int AREA_SPLIT = 5;
    static const int AREA_AMOUNT = AREA_SPLIT * AREA_SPLIT;
    int areaWidth;
    int areaHeight;
    void updateArea(int t_areaNumber);
    std::vector<std::shared_ptr<Pixel>> areas[AREA_AMOUNT]; // A vector of vectors of Pixel pointers

    // Grid
    void drawGrid();
    std::shared_ptr<Pixel> getPixelFromXY(int t_x, int t_y);

    // Debugging
    bool debugMode = false;
};