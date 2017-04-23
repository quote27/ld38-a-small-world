#pragma once
#include "globals.hpp"
// TODO: const correctness.

class SpriteSheet {
  public:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int rows;
    int columns;
    int cheight;
    int cwidth;
    uint32_t cmargin;

    SpriteSheet(SDL_Renderer* renderer, const char* file_path,
                int cheight=21, int cwidth=21, uint32_t cmargin = 2);
    void render(uint32_t id, SDL_Rect dest) const;
};

enum ESprite {
    BLANK = 839
};
