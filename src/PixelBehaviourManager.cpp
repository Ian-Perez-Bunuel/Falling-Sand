#include "../include/PixelBehaviourManager.h"

// Initialize all data for each pixel type
PixelData BehaviourManager::airData(PixelType::AIR, BLACK, airBehaviour);
PixelData BehaviourManager::sandData(PixelType::SAND, YELLOW, sandBehaviour);

void BehaviourManager::airBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size)
{}

void BehaviourManager::sandBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size)
{
    // Helper lamdba function used to easily get the pixels on the grid
    int x = (t_position.x / t_size);
    int y = (t_position.y / t_size);

    auto getAt = [&](int dx, int dy) -> std::shared_ptr<Pixel> // [&] means it will copy everything inside the object
    {
        int nx = x + dx;
        int ny = y + dy;
        if (nx < 0 || ny < 0 || nx >= t_width || ny >= t_height) return nullptr;
        return t_worldPixels[nx + ny * t_width];
    };

    // Get the pixel being updated
    std::shared_ptr<Pixel> current = getAt(0, 0);
    // Each possible area to go to
    std::shared_ptr<Pixel> below = getAt(0, 1);
    std::shared_ptr<Pixel> bottomRight = getAt(1, 1);
    std::shared_ptr<Pixel> bottomLeft = getAt(-1, 1);

    if (below && below->getType() == PixelType::AIR)
    {
        below->setData(&sandData); // Set the pixel under to be the new type
        below->updated = true;
        current->setData(&airData);
    }
    else if (bottomRight && bottomRight->getType() == PixelType::AIR)
    {
        bottomRight->setData(&sandData); // Set the pixel under to be the new type
        bottomRight->updated = true;
        current->setData(&airData);
    }
    else if (bottomLeft && bottomLeft->getType() == PixelType::AIR)
    {
        bottomLeft->setData(&sandData); // Set the pixel under to be the new type
        bottomLeft->updated = true;
        current->setData(&airData);
    }
}