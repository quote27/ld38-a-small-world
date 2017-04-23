#include "entity.hpp"

void Entity::draw() {
    SDL_Rect r = {(int)x, (int)y, (int)w, (int)h};
    if(spritesheet) {
        spritesheet->render(sprite_id, r);
    }
}
