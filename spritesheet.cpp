#include "spritesheet.hpp"

SpriteSheet::SpriteSheet(SDL_Renderer* renderer,
                         const char* file_path,
                         int cheight,
                         int cwidth,
                         uint32_t cmargin) :
  renderer(renderer),
  cheight(cheight),
  cwidth(cwidth),
  cmargin(cmargin)
{
    SDL_Surface *surface = IMG_Load(file_path);
    rows = surface->h / (cheight + cmargin);
    columns = surface->w / (cwidth + cmargin);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface); /* we got the texture now -> free surface */
};

void SpriteSheet::render(uint32_t id, SDL_Rect destR) const {
    SDL_Rect buffer;
    buffer.w = cwidth;
    buffer.h = cheight;
    buffer.x = (id % columns) * (cwidth + cmargin) + cmargin;
    buffer.y = (id / columns) * (cheight + cmargin) + cmargin;

    /* render the current animation step of our shape */
    SDL_RenderCopyEx(renderer, texture, &buffer, &destR, 0.0, NULL, SDL_FLIP_VERTICAL);
}
