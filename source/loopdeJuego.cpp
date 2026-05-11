#include "loopDeJuego.h"

LoopDeJuego::LoopDeJuego(int screenWidth, int screenHeight)
    : screenWidth(screenWidth)
    , screenHeight(screenHeight)
    , angulo(45.0f * b2_pi / 180.0f)
    , fuerzaActual(0.0f)
    , textoSecundario({ 220, 200, 200, 255 })
{
}

void LoopDeJuego::RunLoop(b2World& world, Ground& ground, Proyectil& proyectil, OtrosCuerpos& edificioIzq, OtrosCuerpos& edificioDer)
{
    HandleInput(world, proyectil);
    Draw(ground, proyectil, edificioIzq, edificioDer);
}

void LoopDeJuego::HandleInput(b2World& world,Proyectil& proyectil)// Ground& ground, 
{
    // Rotar ángulo
    if (IsKeyDown(KEY_Q)) angulo += 0.7f * b2_pi / 180.0f;
    if (IsKeyDown(KEY_T)) angulo -= 1.0f * b2_pi / 180.0f;
    if (angulo < 0.0f)  angulo = 0.0f;
    if (angulo > b2_pi) angulo = b2_pi;

    // Cargar fuerza
    if (IsKeyDown(KEY_SPACE)) {
        fuerzaActual += 0.1f;
        fuerzaActual = fminf(fuerzaActual, FUERZA_MAXIMA);
    }

    // Color según fuerza cargada
    unsigned char r = (unsigned char)(255 * (fuerzaActual / FUERZA_MAXIMA));
    unsigned char g = (unsigned char)(255 * (1.0f - fuerzaActual / FUERZA_MAXIMA));
    proyectil.color = { r, g, 0, 230 };

    // Lanzar al soltar
    if (IsKeyReleased(KEY_SPACE)) {
        proyectil.Lanzar(angulo, fuerzaActual);
        fuerzaActual = 0.0f;
    }

    // Reiniciar
    if (IsKeyPressed(KEY_R)) {
        world.DestroyBody(proyectil.body);
        proyectil = Proyectil(world, SPAWN_X, (float)screenHeight - 80.0f, Fade(ORANGE, 0.9f));
        fuerzaActual = 0.0f;
    }
}

void LoopDeJuego::Draw(Ground& ground, Proyectil& proyectil, OtrosCuerpos& edificioIzq, OtrosCuerpos& edificioDer)
{
    BeginDrawing();
    ClearBackground({ 85, 100, 150, 180 });

    

    // Edificios
    edificioIzq.Draw();
    edificioDer.Draw();
    // Proyectilios
    proyectil.Draw();
    proyectil.Previsualiza(angulo, fuerzaActual);
    proyectil.DebugInfo();

    b2Vec2 vel = proyectil.body->GetLinearVelocity();
    ground.Drawground(vel);

    // HUD
    DrawRectangle(90, 70, 820, 90, Fade(BLACK, 0.18f));
    DrawText("Unidad 2 - Lanzamiento de proyectil", 240, 80, 26, textoSecundario);

    DrawRectangleGradientH(7, 7, 380, 30, RAYWHITE, BLANK);
    DrawText(TextFormat(u8"Ángulo: %.1f°", angulo * 180.0f / b2_pi), 15, 15, 20, RED);
    DrawText(u8"Q / T : rotar ángulo    ESPACIO : acumula y lanza    R : reiniciar", 220, 560, 20, RAYWHITE);
    DrawRectangleGradientH(screenWidth - 387, 7, 380, 30, BLANK, RAYWHITE);
    DrawFPS(900, 15);

    EndDrawing();
}