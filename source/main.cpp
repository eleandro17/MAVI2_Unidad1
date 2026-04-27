#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include <vector>
#include "physicsBox.h"
#include "ground.h"

const float SCALE = 30.0f; // 30 píxeles = 1 metro


int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "MAVI II - Unidad 1. Gomez Viera Emilio Leandro");
    SetTargetFPS(60); // lo pongo en 60 para que se corresponda con la velocidad de simulación

    Color fondo = { 85, 100, 215, 255 };
    Color textoPrincipal = RAYWHITE;
    Color textoSecundario = {220,200,200,255};
    
    // Mundo físico con gravedad estándar
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    // -----------------------------
    // Suelo estático : ahora quedó solo el constructor
    // -----------------------------

    Ground ground(world, screenWidth, screenHeight, Fade(DARKGREEN, 0.7f));
    std::vector<PhysicsBox> boxes;

    float angulo = 0.0f;
    
    while (!WindowShouldClose())
    {
        // Input de rotación
        if (IsKeyDown(KEY_T)) {
            angulo += 2.5f * b2_pi / 180.0f;
        }
        if (IsKeyDown(KEY_Q)) {
            angulo -= 0.5f * b2_pi / 180.0f; // incremento más chico para ajuste fino
        }

        // Spawn de caja en posición del mouse
        if (IsKeyPressed(KEY_SPACE)) {
            PhysicsBox nuevaCaja(world, (float)GetMouseX(), (float)GetMouseY(), angulo, Fade(PINK, 0.55f));
            boxes.push_back(nuevaCaja);
        }

        // Avanzar simulación
        // como se corresponde la velocidad de simulación con la velocidad de dibujado? tienen que ser iguales?
        world.Step(1.0f / 60.0f, 8, 3);

      
        BeginDrawing();
        ClearBackground(fondo);

        // Suelo
        ground.Draw();

        // Dibujar cajas
        for (auto& box : boxes) {
            box.Draw();
        }

        // Panel superior
        DrawRectangle(90, 70, 820, 90, Fade(BLACK, 0.18f));
        DrawText("Unidad 1", 430, 15, 28, textoPrincipal);
        DrawText("Raylib dibuja. Box2D simula.", 310, 80, 28, textoSecundario);

        // Ángulo actual
        DrawRectangleGradientH(7, 7,380, 30, RAYWHITE, BLANK);
        DrawText(TextFormat(u8"Ángulo: %.2f°", angulo * 180.0f / b2_pi), 15,15, 20, RED);

        // Pie
        DrawText(u8"Q y T rotan la caja de previsualización", 330, 560, 20, RAYWHITE);

        // Previsualización en el mouse
        float posX = GetMouseX();
        float posY = GetMouseY();
        Rectangle rect2 = {
            posX ,
            posY ,
            20,
            20
        };
        DrawRectanglePro(rect2, { 10, 10 }, angulo * RAD2DEG, YELLOW);

        DrawRectangleGradientH(1000-387, 7, 380, 30, BLANK, RAYWHITE);
        DrawFPS(900, 15);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}