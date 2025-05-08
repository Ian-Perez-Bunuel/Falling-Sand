#include "../include/World.h"

World::World()
{
    worldPixels.reserve((worldWidth * worldHeight) * sizeof(Pixel)); // Reserve enough space to fill the world

    for (int y = 0; y < worldHeight; y++)
    {
        for (int x = 0; x < worldWidth; x++)
        {
            // Create Pixels
            Vector2 position = {x * pixelSize, y * pixelSize};
            worldPixels.push_back(std::make_shared<Pixel>(position, pixelSize, &BehaviourManager::airData));
        }
    }
}

std::shared_ptr<Pixel> World::getPixelUnderMouse()
{
    if (IsCursorOnScreen())
    {
        float mouseX = GetMousePosition().x;
        float mouseY = GetMousePosition().y;
        
        for (int i = 0; i < worldPixels.size(); i++)
        {
            float pixelX = worldPixels[i]->getPos().x;
            float pixelY = worldPixels[i]->getPos().y;

            if (mouseX >= pixelX - (pixelSize / 2.0f) && mouseX <= pixelX + (pixelSize / 2.0f) &&
                mouseY >= pixelY - (pixelSize / 2.0f) && mouseY <= pixelY + (pixelSize / 2.0f))
            {
                return worldPixels[i];
            }
        }
    }

    return nullptr;
}

void World::spawnOnMouse()
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        std::shared_ptr<Pixel> pixel = getPixelUnderMouse();

        if (pixel != nullptr)
        {
            pixel->setData(&BehaviourManager::sandData);
        }
    }
}

void World::update()
{
    for (int i = 0; i < worldPixels.size(); i++)
    {
        if (!worldPixels[i]->updated)
        {
            worldPixels[i]->update(worldPixels, i, worldWidth, worldHeight);
        }
        else
        {
            worldPixels[i]->updated = false;
        }
    } 

    spawnOnMouse();
}

void World::draw()
{
    for (std::shared_ptr<Pixel> pixel : worldPixels)
    {
        pixel->draw();
    }

    if (debugMode)
    {
        drawGrid();
    }
}

void World::drawGrid()
{
    for (int x = 0; x < GetScreenWidth(); x += 10)
    {
        for (int y = 0; y < GetScreenHeight(); y += 10)
        {
            DrawLine(x, y, x + GetScreenWidth(), y, WHITE);
            DrawLine(x, y, x, y + GetScreenHeight(), WHITE);
        }
    }
}