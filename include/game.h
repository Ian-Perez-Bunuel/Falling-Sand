#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "stdio.h"

#include "../include/World.h"


class Game
{
public:
    void init();
    void draw();
    void update();

private:

    World world;

};

#endif // GAME_H