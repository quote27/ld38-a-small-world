#pragma once
#include "globals.hpp"

class SpriteSheet;

class Player {
    public:
        float x, y;
        float xv, yv;

        static const int h = 40;
        static const int w = 20;

        int sprite_id;
        const SpriteSheet *sheet;

        // these are temporary until spritesheet is done
        SDL_Texture *tex;

        // TODO: this takes in a shared_ptr<SpriteSheet>
        Player(float x, float y, SDL_Renderer *renderer);

        void update();

        void draw(SDL_Renderer *renderer);
};

