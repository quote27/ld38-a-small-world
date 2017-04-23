#pragma once
#include "entity.hpp"
#include "map.hpp"

class Camera {
  private:
    SDL_Renderer *renderer;
    Entity *target;
    SDL_Texture *viewport;
  public:
    int h;
    int w;
    Camera(SDL_Renderer *renderer, Entity *target, SDL_Texture *viewport, int h, int w);

    void draw();
};
