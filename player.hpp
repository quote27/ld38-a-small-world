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
    player_state_e player_state;

    Player(float x, float y, const SpriteSheet *spritesheet);

    void handle_event(SDL_Event *event) final;
    bool update() final;
    void undo();

    void jump();
private:

    bool left_key;
    bool right_key;
    bool action_key;

    float old_x;
    float old_y;
    float old_xv;
    float old_yv;
};
