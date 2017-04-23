#include "player.hpp"
#include "state.hpp"
#include "spritesheet.hpp"

Player::Player(float _x, float _y, SpriteSheet *_spritesheet) {
    x = _x;
    y = _y;
    xv = 0.0f;
    yv = 0.0f;
    sprite_id = 19;
    spritesheet = _spritesheet;
}

void Player::jump() {
    switch(player_state) {
        case GROUND: player_state = JUMP_1_START; break;
        case JUMP_1: player_state = JUMP_2_START; break;
        default: {}
    }
}

void Player::handle_event(SDL_Event *event) {
    if(event->type != SDL_KEYDOWN)
        return;

    switch(event->key.keysym.sym) {
        case SDLK_z:
        case SDLK_SPACE: jump(); break;
        default: {}
    }
}

void Player::update() {
    switch(player_state) {
        case GROUND: yv = 0; break; //do nothing, y-axis doesnt change - TODO: animation change
        case JUMP_2_START:
        case JUMP_1_START: yv = 4; break; //vel[1] = 1; break; //add 'jump' to velocity
        case JUMP_2:
        case JUMP_1: {
                         yv += -gravity * state.fps.speed;
                         y += yv * state.fps.speed;
                         break;
                     }
        default: {}
    }
    if(player_state == JUMP_1_START) {
        player_state = JUMP_1;
    } else if(player_state == JUMP_2_START) {
        player_state = JUMP_2;
    } else if(y <= 0) {
        player_state = GROUND;
        y = 0;
    }
}
