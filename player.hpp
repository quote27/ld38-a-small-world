#pragma once
#include "globals.hpp"
#include "entity.hpp"

class SpriteSheet;

enum player_state_e {
    GROUND,
    JUMP_1_START,
    JUMP_1,
    JUMP_2_START,
    JUMP_2,
};

class Player : public Entity {
    public:
        float x, y;
        float xv, yv;

        static const int h = 40;
        static const int w = 40;

        int sprite_id;
        SpriteSheet *spritesheet;

        // these are temporary until spritesheet is done
        SDL_Texture *tex;

        // TODO: this takes in a shared_ptr<SpriteSheet>
        Player(float x, float y, SDL_Renderer *renderer, SpriteSheet *spritesheet);

        void update();

        void draw(SDL_Renderer *renderer);
};

