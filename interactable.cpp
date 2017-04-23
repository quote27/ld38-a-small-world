#include "interactable.hpp"

Interactable::Interactable(float _x, float _y, const SpriteSheet *_spritesheet, int _sprite_id,
        bool _blocking) : Entity(_spritesheet) {
    init(_x, _y, 0.0f, 0.0f, _sprite_id, _blocking);
}

void Interactable::handle_event(SDL_Event *event) { }

bool Interactable::update() {
    frame_ctr++;

    if(frame_ctr % 10 == 0) {
        frame_ctr = 0;
        sprite_id = (sprite_id == 321) ? 320 : 321;
    }
    return false;
}

void Interactable::undo() { }

void Interactable::resolve_collision(const Entity *other) { }
