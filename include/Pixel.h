#pragma once
#include "raylib.h"
#include "stdio.h"

#include <memory>
#include <vector>

enum class PixelType
{
    AIR,
    SAND
};

class Pixel
{
public:
    Pixel(Vector2 t_pos, float t_size);

    virtual void update(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height);
    virtual void draw();

    PixelType getType() { return type; }
    void setType(PixelType t_type) { type = t_type; }
    Vector2 getPos() { return position; }

    bool updated = false;
protected:
    Vector2 position;

private:
    float size;  
    PixelType type = PixelType::AIR;
};