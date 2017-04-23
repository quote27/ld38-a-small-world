#include "entity.hpp"

void Entity::draw() const {
    SDL_Rect r = {(int)x, (int)y, (int)w, (int)h};
    if(spritesheet) {
        spritesheet->render(sprite_id, r);
    }
}

bool Entity::collide(const Entity *other) const {
    if(!(collideable && other->collideable)) {
        return false;
    }

    // compare bounding boxes
    return !(other->x > this->x + this->w
            || other->x + other->w < this->x
            || other->y + other->h < this->y
            || other->y > this->y + this->h);
}
