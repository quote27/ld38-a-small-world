#pragma once
#include "globals.hpp"

class SpriteSheet;

class Player {
    public:
        float x, y;
        float xv, yv;

        int sprite_id;
        shared_ptr<SpriteSheet> sheet;

        // TODO: this takes in a shared_ptr<SpriteSheet>
        Player(float x, float y);

        void update();

        void draw();
};

