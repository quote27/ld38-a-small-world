#pragma once
#include "globals.hpp"
#include "entity.hpp"

enum player_state_e {
    GROUND,
    JUMP_1_START,
    JUMP_1,
    JUMP_2_START,
    JUMP_2,
};

class Player : public Entity {
public:
    static const int h = 40;
    static const int w = 40;

    player_state_e player_state;

    Player(float x, float y, SpriteSheet *spritesheet);

    void handle_event(SDL_Event *event) final;
    void update() final;

    void jump();
};
