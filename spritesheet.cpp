#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(SDL_Renderer* _renderer,
                         const char* file_path,
                         uint32_t _margin) :
  renderer(_renderer),
  margin(_margin)
{
    buffer.h = 21;
    buffer.w = 21;
    buffer.x = 0;
    buffer.y = 0;

    SDL_Surface *surface = IMG_Load(file_path);
    rows = surface->h / (buffer.h + margin);
    columns = surface->w / (buffer.w + margin);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); /* we got the texture now -> free surface */
};

void SpriteSheet::render(uint32_t id, SDL_Rect destR) {
    buffer.x = (id % columns) * (buffer.w + margin) + margin;
    buffer.y = (id / columns) * (buffer.h + margin) + margin;

    /* render the current animation step of our shape */
    SDL_RenderCopy(renderer, texture, &buffer, &destR);
    SDL_RenderPresent(renderer);
}
