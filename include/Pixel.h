#pragma once

#include "../include/PixelBehaviourManager.h"

class Pixel
{
public:
    Pixel(Vector2 t_pos, float t_size, PixelData* t_data);

    virtual void update(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height);
    virtual void draw();

    void setData(PixelData* t_data) { data = t_data; }

    PixelType getType() { return data->type; }
    void setType(PixelType t_type) { data->type = t_type; }

    Vector2 getPos() { return position; }

    bool updated = false;
protected:
    Vector2 position;
    PixelData* data;    // Reference to the data needed
    float size;  

private:
};