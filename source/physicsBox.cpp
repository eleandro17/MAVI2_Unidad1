#include "PhysicsBox.h"

PhysicsBox::PhysicsBox(b2World& world, float posX, float posY, float angle, Color col)
    : width(50.0f), height(50.0f), color(col)
{
    b2BodyDef boxDef;
    boxDef.type = b2_dynamicBody;
    boxDef.position.Set(posX / SCALE, posY / SCALE);
    boxDef.angle = angle;
    
    body = world.CreateBody(&boxDef);

    b2PolygonShape boxShape;
    boxShape.SetAsBox(25.0f / SCALE, 25.0f / SCALE);

    b2FixtureDef boxFixture;
    boxFixture.shape = &boxShape;
    boxFixture.density = 1.0f;
    boxFixture.friction = 0.4f;
    boxFixture.restitution = 0.2f;

    body->CreateFixture(&boxFixture);
}

void PhysicsBox::Draw()
{
    b2Vec2 pos = body->GetPosition();
    float angle = body->GetAngle() * RAD2DEG;

    // DrawRectanglePro toma la posición como esquina superior izquierda
    // pasando el centro directo y origin = half-size, el pivote queda bien centrado
    Rectangle rect = {
        pos.x * SCALE,
        pos.y * SCALE,
        width,
        height
    };
    Vector2 origin = { width / 2.0f, height / 2.0f };

    DrawRectanglePro(rect, origin, angle, color);

    // rect separado para el borde (DrawRectangleLinesEx no usa origin)
    Rectangle rectLines = {
        pos.x * SCALE - width / 2.0f,
        pos.y * SCALE - height / 2.0f,
        width,
        height
    };
    DrawRectangleLinesEx(rectLines, 2, DARKBLUE);
}