#include "interactable.hpp"

Interactable::Interactable(float _x, float _y, const SpriteSheet *_spritesheet, int _sprite_id,
        bool _collideable) : Entity(_spritesheet) {
    x = _x;
    y = _y;
    xv = 0.0f;
    yv = 0.0f;
    sprite_id = _sprite_id;
    collideable = _collideable;
}

void Interactable::handle_event(SDL_Event *event) {
}

bool Interactable::update() {
    frame_ctr++;

    if(frame_ctr % 10 == 0) {
        frame_ctr = 0;
        sprite_id = (sprite_id == 321) ? 322 : 321;
    }
    return false;
}
