#include "../include/Pixel.h"


Pixel::Pixel(Vector2 t_pos, float t_size)
    : position(t_pos), size(t_size)
{
    type = PixelType::AIR;
}

void Pixel::update(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height)
{
    if (type == PixelType::SAND)
    {
        // Helper lamdba function used to easily get the pixels on the grid
        int x = (position.x / size);
        int y = (position.y / size);

        auto getAt = [&](int dx, int dy) -> std::shared_ptr<Pixel> // [&] means it will copy everything inside the object
        {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || ny < 0 || nx >= t_width || ny >= t_height) return nullptr;
            return t_worldPixels[nx + ny * t_width];
        };

        // Each possible area to go to
        std::shared_ptr<Pixel> below = getAt(0, 1);
        std::shared_ptr<Pixel> bottomRight = getAt(1, 1);
        std::shared_ptr<Pixel> bottomLeft = getAt(-1, 1);

        if (below && below->getType() == PixelType::AIR)
        {
            below->setType(type); // Set the pixel under to be the new type
            below->updated = true;
            type = PixelType::AIR; // Empty the above pixel
        }
        else if (bottomRight && bottomRight->getType() == PixelType::AIR)
        {
            bottomRight->setType(type); // Set the pixel under to be the new type
            bottomRight->updated = true;
            type = PixelType::AIR; // Empty the above pixel
        }
        else if (bottomLeft && bottomLeft->getType() == PixelType::AIR)
        {
            bottomLeft->setType(type); // Set the pixel under to be the new type
            bottomLeft->updated = true;
            type = PixelType::AIR; // Empty the above pixel
        }
    }
}


void Pixel::draw()
{
    if (type == PixelType::SAND)
    {
        DrawRectangle(position.x, position.y, size, size, YELLOW);
    }
}