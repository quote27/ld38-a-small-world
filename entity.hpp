#pragma once
#include "globals.hpp"
#include "spritesheet.hpp"

class Entity {
public:
    float x;
    float y;
    float xv;
    float yv;

    static const int h = SPRITE_SIZE;
    static const int w = SPRITE_SIZE;

    int sprite_id; // -1 for no sprite
    SpriteSheet *spritesheet;

    virtual void handle_event(SDL_Event *event) = 0;
    virtual void update() = 0;
    virtual void draw();

    Entity() : x(0.0f), y(0.0f), xv(0.0f), yv(0.0f),
               sprite_id(-1), spritesheet(nullptr) {}
    ~Entity() {
        if(spritesheet) {
            delete spritesheet;
        }
    }
};
