#include "camera.hpp"

Camera::Camera(SDL_Renderer *renderer, Entity *target, Map *map, int h, int w) :
    renderer(renderer), target(target), map(map), h(h), w(w)
{
    x = target->x;
    y = target->y;
    viewport = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                 SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
};

void Camera::draw() {
    SDL_Rect buffer;
    x = target->x - w/2;
    y = target->y - h/2;
    if (x < 0) { x = 0; }
    if (x > map->get_width()) { x = map->get_width(); }
    if (y < 0) { y = 0; }
    if (y > map->get_height()) { y = map->get_height(); }

    buffer.x = x;
    buffer.y = y;
    buffer.h = h;
    buffer.w = w;
    SDL_SetRenderTarget(renderer, NULL);
    // TODO: if we do this, we can pretend that the bottom left is 0,0
    // however we'll have to flip all the sprites as we render them
    // this might be ok as spritesheet will handle that
    SDL_RenderCopyEx(renderer, viewport, &buffer, NULL, 0.0, NULL, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);
}

Camera::~Camera() {
    SDL_DestroyTexture(viewport);
}
