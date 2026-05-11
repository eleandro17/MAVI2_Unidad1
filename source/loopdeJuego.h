#pragma once

#include "raylib.h"
#include <box2d.h>
#include "ground.h"
#include "Proyectil.h"
#include "OtrosCuerpos.h"

class LoopDeJuego
{
public:
    LoopDeJuego(int screenWidth, int screenHeight);
            
    void RunLoop(b2World& world, Ground& ground, Proyectil& proyectil, OtrosCuerpos& edificioIzq, OtrosCuerpos& edificioDer);

private:
    int   screenWidth;
    int   screenHeight;

    float angulo;
    float fuerzaActual;

    static constexpr float FUERZA_MAXIMA = 25.0f;
    static constexpr float SPAWN_X = 150.0f;

    Color textoSecundario;

    void HandleInput(b2World& world, Proyectil& proyectil);// Ground& ground,
    void Draw(Ground& ground, Proyectil& proyectil, OtrosCuerpos& edificioIzq, OtrosCuerpos& edificioDer);
};