#include "player.hpp"
#include "state.hpp"

Player::Player(float x, float y) : x(x), y(y), xv(0.0f), yv(0.0f) {
    sprite_id = 3;
}

void Player::update() {
    switch(state.player_state) {
        case GROUND: yv = 0; break; //do nothing, y-axis doesnt change - TODO: animation change
        case JUMP_2_START:
        case JUMP_1_START: yv = 4; break; //vel[1] = 1; break; //add 'jump' to velocity
        case JUMP_2:
        case JUMP_1: {
                         yv += -gravity * state.fps.speed;
                         y += yv * state.fps.speed;
                         break;
                     }
    }
    if(state.player_state == JUMP_1_START) {
        state.player_state = JUMP_1;
    } else if(state.player_state == JUMP_2_START) {
        state.player_state = JUMP_2;
    } else if(y <= 0) {
        state.player_state = GROUND;
        y = 0;
    }
}

void draw() {

}
