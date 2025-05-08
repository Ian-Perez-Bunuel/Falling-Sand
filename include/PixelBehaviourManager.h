#pragma once
#include "raylib.h"
#include "stdio.h"

#include <memory>
#include <vector>

class Pixel;

enum class PixelType
{
    AIR,
    SAND
};

struct PixelData
{
    PixelData(PixelType t_type, Color t_color, void (*t_behaviour)(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size))
        : type(t_type), color(t_color), behaviour(t_behaviour)
    {
    }
    PixelType type;
    Color color;
    // float density;   // Used for displacement of more dense materials
    // float mass;      // Used for speed / velocity calcs when added
    void (*behaviour)(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size);
};

class BehaviourManager
{
public:
    static PixelData airData; // (PixelType::AIR, BLACK, airBehaviour)
    static PixelData sandData; //(PixelType::SAND, YELLOW, sandBehaviour)

private:
    // Each type of behaviour
    static void airBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size);
    static void sandBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size);
};


#include "../include/Pixel.h"