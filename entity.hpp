#pragma once
#include "globals.hpp"
#include "spritesheet.hpp"

class Entity {
public:
    static const int h = SPRITE_SIZE;
    static const int w = SPRITE_SIZE;

    float x;
    float y;
    float xv;
    float yv;

    int sprite_id; // -1 for no sprite
    const SpriteSheet *spritesheet;

    bool blocking;

    virtual void handle_event(SDL_Event *event) = 0;
    virtual bool update() = 0;
    virtual bool collide(const Entity *other) const;
    virtual void draw() const;
    virtual void undo() = 0;

    Entity(const SpriteSheet *spritesheet) : x(0.0f), y(0.0f), xv(0.0f), yv(0.0f),
           sprite_id(BLANK), spritesheet(spritesheet), blocking(false) {}

protected:
    void init(float _x, float _y, float _xv, float _yv, int _sprite_id, bool _blocking);
};
