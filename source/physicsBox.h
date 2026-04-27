#pragma once

#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

class PhysicsBox
{
public:
    b2Body* body;
    float width;
    float height;
    Color color;

    PhysicsBox(b2World& world, float posX, float posY, float angle, Color col);
    void Draw();
};