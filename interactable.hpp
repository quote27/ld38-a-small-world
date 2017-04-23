#pragma once
#include "globals.hpp"
#include "entity.hpp"

class Interactable : public Entity {
public:
    int frame_ctr;

    Interactable(float _x, float _y, const SpriteSheet *_spritesheet, int _sprite_id, bool _collideable);

    void handle_event(SDL_Event *event) final;
    bool update() final;
    void undo();
};
