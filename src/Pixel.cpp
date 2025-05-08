#include "../include/Pixel.h"


Pixel::Pixel(Vector2 t_pos, float t_size, PixelData* t_data)
    : position(t_pos), size(t_size), data(t_data)
{
}

void Pixel::update(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height)
{
    data->behaviour(t_worldPixels, t_index, t_width, t_height, position, size);
}


void Pixel::draw()
{
    if (data->type == PixelType::SAND)
    {
        DrawRectangle(position.x, position.y, size, size, data->color);
    }
}