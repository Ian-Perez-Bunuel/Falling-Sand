#include "raylib.h"
#include "stdio.h"
#include "../include/game.h"

void Game::init()
{
    world.init();
}

void Game::draw()
{
    world.draw();
    
    DrawFPS(0, 0);
}

void Game::update()
{
    world.update();
}
