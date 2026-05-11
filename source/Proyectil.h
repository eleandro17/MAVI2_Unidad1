#pragma once

#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

class Proyectil
{
public:
    b2Body* body;
    float radius;
    Color color;
    bool lanzado;

    Proyectil(b2World& world, float posX, float posY, Color col);
    void Lanzar(float angleRad, float force);
    void Draw();
    void Previsualiza(float angulo, float fuerzaActual);
    void DebugInfo();
};

