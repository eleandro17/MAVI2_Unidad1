#pragma once
#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

class OtrosCuerpos
{
public:
    // ancho y alto en pixels
    OtrosCuerpos(b2World& world, float posX, float posY,float anchoPixels, float altoPixels);

    void Draw() const;
        
    b2Body* stbody;
    

private:
    float anchoPixels;
    float altoPixels;
    float posX, posY; // posicion del centro
    
};