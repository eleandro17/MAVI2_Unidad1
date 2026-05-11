#include "OtrosCuerpos.h"

OtrosCuerpos::OtrosCuerpos(b2World& world,float posX, float posY, float anchoPixels, float altoPixels)
    : anchoPixels(anchoPixels), altoPixels(altoPixels),
    posX(posX), posY(posY)
{
    // no se mueve, pero el proyectil le pega, entonces un staticbody
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(posX / SCALE, posY / SCALE);

    stbody = world.CreateBody(&bodyDef);

    // caja centrada en el body
    b2PolygonShape boxShape;
    boxShape.SetAsBox((anchoPixels / 2.0f) /SCALE,(altoPixels / 2.0f) / SCALE);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &boxShape;
    fixtureDef.density = 0.0f;   
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.3f;  
    stbody->CreateFixture(&fixtureDef);
}

void OtrosCuerpos::Draw() const
{
    
    b2Vec2 pos = stbody->GetPosition();
    float cx = pos.x * SCALE;//l a misma escala
    float cy = pos.y * SCALE;
    
//b2Vec2 velproyectil = proyectil->GetLinearVelocity();//--------------------------------------------------->>>>
    

    // DrawRectangle recibe esq izq-arriba
    int rx = (int)(cx - anchoPixels / 2.0f);
    int ry = (int)(cy - altoPixels / 2.0f);

    DrawRectangle(rx, ry, (int)anchoPixels, (int)altoPixels, Fade(DARKPURPLE, 0.85f));
    //DrawRectangleLines(rx, ry, velproyectil.x*SCALE,velproyectil.y*SCALE, YELLOW);

    
}