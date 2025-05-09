#include "../include/PixelBehaviourManager.h"

// Initialize all data for each pixel type
PixelData BehaviourManager::airData(PixelType::AIR, BLACK, AIR_DENSITY, airBehaviour);
PixelData BehaviourManager::sandData(PixelType::SAND, YELLOW, SAND_DENSITY, sandBehaviour);
PixelData BehaviourManager::waterData(PixelType::WATER, BLUE, WATER_DENSITY, waterBehaviour);

void BehaviourManager::moveFrom(std::shared_ptr<Pixel> t_current, PixelData& t_currentData, std::shared_ptr<Pixel> t_newPlace)
{
    t_newPlace->setData(&t_currentData); // Set the pixel under to be the new type
    t_newPlace->updated = true;
    t_current->setData(&airData);
}

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
    PixelData& currentData = current->getData();
    // Each possible area to go to
    std::shared_ptr<Pixel> below = getAt(0, 1);
    std::shared_ptr<Pixel> bottomRight = getAt(1, 1);
    std::shared_ptr<Pixel> bottomLeft = getAt(-1, 1);

    if (below && below->getData().density < currentData.density)
    {
        moveFrom(current, currentData, below);
    }
    else if (bottomRight && bottomRight->getData().density < currentData.density)
    {
        moveFrom(current, currentData, bottomRight);
    }
    else if (bottomLeft && bottomLeft->getData().density < currentData.density)
    {
        moveFrom(current, currentData, bottomLeft);
    }
}

void BehaviourManager::waterBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size)
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
    PixelData& currentData = current->getData();
    // Each possible area to go to
    std::shared_ptr<Pixel> below = getAt(0, 1);
    std::shared_ptr<Pixel> bottomRight = getAt(1, 1);
    std::shared_ptr<Pixel> right = getAt(1, 0);
    std::shared_ptr<Pixel> bottomLeft = getAt(-1, 1);
    std::shared_ptr<Pixel> left = getAt(-1, 0);

    if (below && below->getData().density < currentData.density)
    {
        moveFrom(current, currentData, below);
    }
    else if (bottomRight && bottomRight->getData().density < currentData.density)
    {
        moveFrom(current, currentData, bottomRight);
    }
    else if (bottomLeft && bottomLeft->getData().density < currentData.density)
    {
        moveFrom(current, currentData, bottomLeft);
    }
    else if (right && right->getData().density < currentData.density)
    {
        moveFrom(current, currentData, right);
    }
    else if (left && left->getData().density < currentData.density)
    {
        moveFrom(current, currentData, left);
    }
}