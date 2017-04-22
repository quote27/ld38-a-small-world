#pragma once
#include "globals.hpp"

class Entity {
public:
    float x;
    float y;
    float xv;
    float yv;

    int sprite_id; // -1 for no sprite
    SpriteSheet *sheet;


};
