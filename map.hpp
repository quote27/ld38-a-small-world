#pragma once
#include<vector>
#include "spritesheet.hpp"

class Map {
  public:
    int rows;
    int columns;
    std::vector<std::vector<int>> tiles;
    SDL_Texture *texture;
    Map(SDL_Renderer *renderer, const SpriteSheet *spritesheet, int rows, int columns);

    int get_height() { return height; };
    int get_width() { return width; };

    void compose();
    void draw();

  private:
    SDL_Renderer* renderer;
    const SpriteSheet* spritesheet;
    int height = 0;
    int width = 0;
};
