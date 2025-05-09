#include "../include/World.h"

void World::init()
{
    calcWorldDimensions();
    worldPixels.reserve((worldWidth * worldHeight) * sizeof(Pixel)); // Reserve enough space to fill the world

    // Fill in the Area with air
    for (int y = 0; y < worldHeight; y++)
    {
        for (int x = 0; x < worldWidth; x++)
        {
            // Create Pixels
            Vector2 position = {x * PIXEL_SIZE, y * PIXEL_SIZE};
            worldPixels.push_back(std::make_shared<Pixel>(position, PIXEL_SIZE, &BehaviourManager::airData));
        }
    }
    
    // Give each area their Pixels from the world
    areaWidth = worldWidth / AREA_SPLIT;
    areaHeight = worldHeight / AREA_SPLIT;
    int currentArea = 0;
    // Populate each area
    for (int rows = 0; rows < AREA_SPLIT; rows++)
    {
        for (int colms = 0; colms < AREA_SPLIT; colms++)
        {
            for (int x = 0; x < areaWidth; x++)
            {
                for (int y = 0; y < areaHeight; y++)
                {
                    areas[currentArea].push_back(getPixelFromXY(x + (rows * areaWidth), y + (colms * areaHeight)));
                }
            }
            currentArea++;
        }
    }
}

void World::calcWorldDimensions()
{
    worldWidth = GetScreenWidth() / PIXEL_SIZE;
    worldHeight = GetScreenHeight() / PIXEL_SIZE;
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

            if (mouseX >= pixelX - (PIXEL_SIZE / 2.0f) && mouseX <= pixelX + (PIXEL_SIZE / 2.0f) &&
                mouseY >= pixelY - (PIXEL_SIZE / 2.0f) && mouseY <= pixelY + (PIXEL_SIZE / 2.0f))
            {
                return worldPixels[i];
            }
        }
    }

    return nullptr;
}

void World::spawnOnMouse()
{
    std::shared_ptr<Pixel> pixel = getPixelUnderMouse();

    if (pixel != nullptr)
    {  
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            pixel->setData(&BehaviourManager::sandData); 
        }
        else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            pixel->setData(&BehaviourManager::waterData);  
        }
    }
}

void World::updateArea(int t_areaNumber)
{
    for (int i = 0; i < areas[t_areaNumber].size(); i++)
    {
        if (!areas[t_areaNumber][i]->updated)
        {
            areas[t_areaNumber][i]->update(worldPixels, i, worldWidth, worldHeight);
        }
        else
        {
            areas[t_areaNumber][i]->updated = false;
        }
    }
}

void World::update()
{
    // Commands
    if (IsKeyPressed(KEY_F1))
    {
        debugMode = !debugMode;
    }

    for (int i = 0; i < AREA_AMOUNT; i++)
    {
        updateArea(i);
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

std::shared_ptr<Pixel> World::getPixelFromXY(int t_x, int t_y)
{
    // Bounds check
    if (t_x < 0 || t_x >= worldWidth || t_y < 0 || t_y >= worldHeight)
    {
        return nullptr;
    }

    int index = t_y * worldWidth + t_x;
    return worldPixels[index];
}