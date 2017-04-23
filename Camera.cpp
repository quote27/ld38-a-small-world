#include "camera.hpp"

Camera::Camera(SDL_Renderer *renderer, Entity *target, SDL_Texture *viewport, int h, int w) :
    renderer(renderer), target(target), viewport(viewport), h(h), w(w) {};

void Camera::draw() {
    SDL_Rect buffer;
    buffer.x = target->x;
    buffer.y = target->y;
    buffer.h = h;
    buffer.w = w;
    SDL_SetRenderTarget(renderer, NULL);
    // TODO: if we do this, we can pretend that the bottom left is 0,0
    // however we'll have to flip all the sprites as we render them
    // this might be ok as spritesheet will handle that
    SDL_RenderCopyEx(renderer, viewport, &buffer, NULL, 0.0, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);
}
