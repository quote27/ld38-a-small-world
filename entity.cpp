#include "entity.hpp"


void Entity::init(float _x, float _y, float _xv, float _yv, int _sprite_id, bool _blocking) {
    x = _x;
    y = _y;
    xv = _xv;
    yv = _yv;
    sprite_id = _sprite_id;
    blocking = _blocking;
}

void Entity::draw() const {
    SDL_Rect r = {(int)x, (int)y, (int)w, (int)h};
    if(spritesheet) {
        spritesheet->render(sprite_id, r);
    }
}

bool Entity::collide(const Entity *other) const {
    return !(other->x > this->x + this->w
            || other->x + other->w < this->x
            || other->y + other->h < this->y
            || other->y > this->y + this->h);
}
