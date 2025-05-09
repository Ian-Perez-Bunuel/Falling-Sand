#pragma once
#include "raylib.h"
#include "stdio.h"

#include <memory>
#include <vector>

class Pixel;

// Densities (looked up by g/cm³)
#define AIR_DENSITY 0.001f
#define SAND_DENSITY 1.5f
#define WATER_DENSITY 1.0f

enum class PixelType
{
    AIR,
    SAND,
    WATER
};

struct PixelData
{
    PixelData(PixelType t_type, Color t_color, float t_density, void (*t_behaviour)(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size))
        : type(t_type), color(t_color), density(t_density), behaviour(t_behaviour)
    {
    }
    PixelType type;
    Color color;
    float density;   // Used for laying of densities (like oil and water)
    // float mass;      // Used for speed / velocity calcs when added
    void (*behaviour)(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size);
};

class BehaviourManager
{
public:
    static PixelData airData; 
    static PixelData sandData; 
    static PixelData waterData; 

private:
    //
    static void moveFrom(std::shared_ptr<Pixel> t_current, PixelData& t_currentData, std::shared_ptr<Pixel> t_newPlace);

    // Each type of behaviour
    static void airBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size);
    static void sandBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size);
    static void waterBehaviour(const std::vector<std::shared_ptr<Pixel>>& t_worldPixels, int t_index, int t_width, int t_height, Vector2 t_position, float t_size);
};


#include "../include/Pixel.h"