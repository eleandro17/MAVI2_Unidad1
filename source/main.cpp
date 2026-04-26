#ifndef NDEBUG
#include <vld.h>
#endif

#include "raylib.h"
#include <box2d.h>
#include <vector>


struct PhysicsBox
{
    b2Body* body;
    float width;   // en píxeles
    float height;  // en píxeles
    Color color;
    float angulo;// agrego angulo
    
};

int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 600;
    const float SCALE = 30.0f; // 30 píxeles = 1 metro

    InitWindow(screenWidth, screenHeight, "MAVI II - Unidad 1. Gomez Viera Emilio Leandro");
    SetTargetFPS(60);// lo pongo en 60 para que se corresponda conn la velocidad de simulación, pero no se realmente como va.

    Color fondo = { 110, 100, 215, 255 };
    Color textoPrincipal = RAYWHITE;
    Color textoSecundario = DARKPURPLE;
    Color sueloColor = Fade(DARKGREEN, 0.7f);

        
    // Mundo físico con gravedad estándar
    b2Vec2 gravity(0.0f, 9.8f);
    b2World world(gravity);

    
    // -----------------------------
    // Suelo estático
    // -----------------------------
    b2BodyDef groundDef;
    groundDef.type = b2_staticBody;
    groundDef.position.Set((screenWidth / 2.0f) / SCALE, (screenHeight - 40.0f) / SCALE);
    b2Body* groundBody = world.CreateBody(&groundDef);

    b2PolygonShape groundShape;
    groundShape.SetAsBox((screenWidth / 2.0f) / SCALE, 20.0f / SCALE);
    groundBody->CreateFixture(&groundShape, 0.0f);

    std::vector<PhysicsBox> boxes;

    // -----------------------------
    // Crear algunas cajas dinámicas
    // -----------------------------
   float angulo = 0.0f;

    while (!WindowShouldClose())
    {
        

        if (IsKeyDown(KEY_T)) {
           
            angulo += 2.5f * b2_pi / 180.0f;

        }
        if (IsKeyDown(KEY_Q)) {

            angulo -= 0.5f * b2_pi / 180.0f;// le puse un incremento mucho mas chico acá para que sea posible ajustar mas finamente el angulo

        }
        if (IsKeyPressed(KEY_SPACE)) {
            b2BodyDef boxDef;
            boxDef.type = b2_dynamicBody;
            boxDef.position.Set(GetMouseX() / SCALE, GetMouseY() / SCALE);//uso  la posicion del mouse y lo divido por SCALE que en el draw lo multiplico para fixear la escala
            
            boxDef.angle = angulo;// agrego el angulo de la bodydef y la igualo a mi input

            b2Body* boxBody = world.CreateBody(&boxDef);

            b2PolygonShape boxShape;
            boxShape.SetAsBox(25.0f / SCALE, 25.0f / SCALE);
           
            b2FixtureDef boxFixture;
            boxFixture.shape = &boxShape;
            boxFixture.density = 1.0f;
            boxFixture.friction = 0.4f;
            boxFixture.restitution = 0.2f;

            boxBody->CreateFixture(&boxFixture);

            boxes.push_back({ boxBody, 50.0f, 50.0f, Fade(RED, 0.95f), angulo });
        }
        // Avanzar simulación
        world.Step(1.0f / 60.0f, 8, 3);//como se corresponde la velocidad de simulación con la velocidad de dibujado? tienen que ser iguales?

        BeginDrawing();
        ClearBackground(fondo);

        // el suelo
        DrawRectangle(0, screenHeight - 60, screenWidth, 40, sueloColor);

                
         // Dibujar cajas
        for (const auto& box : boxes)
        {
            b2Vec2 pos = box.body->GetPosition();
            float angle = box.body->GetAngle() * RAD2DEG;

            //Rectangle rect = {
            //    pos.x * SCALE - box.width/2.0f ,
            //    pos.y * SCALE - box.height/2.0f,
            //    box.width,
            //    box.height
            //};

            //Vector2 origin = { box.width / 4.0f, box.height / 4.0f };
            //DrawRectanglePro(rect, origin, angle, box.color);
            //
            //DrawRectangleLinesEx(rect, 2, DARKBLUE);

            Rectangle rect = {
            pos.x * SCALE,        // el calculo del centro lo hago en origin directamente porque me daba un bug la colision
            pos.y * SCALE,        // ← osea, la resta que estaba no esta mas
            box.width,
            box.height
            };

            Vector2 origin = { box.width / 2.0f, box.height / 2.0f };

            DrawRectanglePro(rect, origin, angle, box.color);

            // Para que DrawRectangleLinesEx siga coincidiendo, calculá su rect por separado
            Rectangle rectLines = {
                pos.x * SCALE - box.width / 2.0f,
                pos.y * SCALE - box.height / 2.0f,
                box.width,
                box.height
            };
            DrawRectangleLinesEx(rectLines, 2, DARKBLUE);

            DrawCircle(pos.x * SCALE, pos.y * SCALE, 3, YELLOW); //este circulito me sirve para ver donde esta el centro de box2D
        }

        // Panel superior
        DrawRectangle(90, 70, 820, 90, Fade(BLACK, 0.18f));
        DrawText("Unidad 1", 120, 90, 28, textoPrincipal);
        DrawText("Raylib dibuja. Box2D simula.", 320, 125, 22, textoSecundario);

        // los grados del boxshape
        DrawText(TextFormat(u8"Ángulo: %.2f°", angulo * 180.0f / b2_pi), 10, 10, 20, RED);

        // Pie
        DrawText(u8"Q y T rotan la caja de previsualización", 320, 540, 20, RAYWHITE);

        // previsualizacion cajas/


        float posX = GetMouseX();
        float posY = GetMouseY();


        Rectangle rect2 = {posX  , posY,20, 20 };

        DrawRectanglePro(rect2, {10,10 }, angulo * RAD2DEG, LIME);// el cuadradito para previsualizar
        DrawFPS(800, 35);

        

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
