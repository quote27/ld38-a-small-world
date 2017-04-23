#pragma once
#include "entity.hpp"
#include "map.hpp"

class Camera {
  private:
    SDL_Renderer *renderer;
    Entity *target;
    Map *map;
  public:
    int x;
    int y;
    int h;
    int w;
    SDL_Texture *viewport;

    Camera(SDL_Renderer *renderer, Entity *target, Map *map, int h, int w);
    ~Camera();

    void draw();
};
