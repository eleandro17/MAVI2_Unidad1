#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "ground.h"
#include "Proyectil.h"
#include "Init.h"
#include "loopdeJuego.h"
#include "OtrosCuerpos.h"  

const float SCALE = 30.0f; // 30 píxeles = 1 metro


int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    Init::InitVentana(screenWidth, screenHeight, "MAVI II - Unidad 2. Gomez Viera Emilio Leandro", 60);

    // Colores 
    Color fondo = { 85, 100, 215, 255 };
    Color textoSecundario = { 220, 200, 200, 255 };

   
    // -- Gravedad de Box2d
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // Piso y spawneo de proyectil
    Ground    ground(world, screenWidth, screenHeight);
    Proyectil proyectil(world, 150.0f, (float)screenHeight - 80.0f, Fade(ORANGE, 0.9f));

    // Edificios:
    // Edificio izquierdo: cerca del spawn pero sin bloquearlo
    OtrosCuerpos edificioIzq(world, 300.0f, (float)screenHeight - 130.0f, 60.0f, 200.0f);

    // Edificio derecho: del otro lado de la pantalla
    OtrosCuerpos edificioDer(world, 720.0f, (float)screenHeight - 180.0f, 60.0f, 300.0f);

    // La instancia de JUego
    LoopDeJuego loop(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        world.Step(1.0f / 60.0f, 8, 3);
        loop.RunLoop(world, ground, proyectil, edificioIzq, edificioDer);
    }

    Init::Cerrar();
    return 0;
}