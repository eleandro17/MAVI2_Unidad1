#include "Proyectil.h"

Proyectil::Proyectil(b2World& world, float posX, float posY, Color col)
    : radius(20.0f), color(col), lanzado(false)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(posX / SCALE, posY / SCALE);

    body = world.CreateBody(&bodyDef);

    b2CircleShape circleShape;
    circleShape.m_radius = radius / SCALE;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circleShape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = .4f;
    fixtureDef.restitution = 0.45f;

    body->CreateFixture(&fixtureDef);
}

void Proyectil::Lanzar(float angleRad, float force)
{
    if (lanzado) return;

    b2Vec2 impulse(
        force * cosf(angleRad),
        -force * sinf(angleRad)   // negativo 
    );
    body->ApplyLinearImpulseToCenter(impulse, true);// acáel impulso lineal de box2D
    lanzado = true;
}

void Proyectil::Draw()
{
    b2Vec2 pos = body->GetPosition();
    float screenX = pos.x * SCALE;
    float screenY = pos.y * SCALE;

    
    DrawCircle((int)screenX, (int)screenY, radius, color);
    DrawCircleLines((int)screenX, (int)screenY, radius, DARKBLUE);
}
void Proyectil::Previsualiza(float angulo,float fuerzaActual)
{
    if (!lanzado)
    {
        b2Vec2 pos = body->GetPosition();
        float screenX = pos.x * SCALE;
        float screenY = pos.y * SCALE;

        float largo = 4.0f + (fuerzaActual*3) ;
        float endX = screenX + largo * cosf(angulo);
        float endY = screenY - largo * sinf(angulo);
        DrawLineEx({ screenX, screenY }, { endX, endY }, 3.0f, RED);
        DrawCircle((int)endX, (int)endY, 2, YELLOW);
        
    }
}
//estemetodo se puede descomentar o no
void Proyectil::DebugInfo()
{
    b2Vec2 pos = body->GetPosition();
    b2Vec2 vel = body->GetLinearVelocity();

    float screenX = pos.x * SCALE;
    float screenY = pos.y * SCALE;

    // Dibuja un vector que muestra hacia dónde va y qué tan rápido
    float escala = 5.0f;
    DrawLineEx(
        { screenX, screenY },
        { screenX + vel.x * escala, screenY + vel.y * escala },
        2.0f, YELLOW
    );
}