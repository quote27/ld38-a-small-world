#include "player.hpp"
#include "state.hpp"
#include "spritesheet.hpp"

Player::Player(float _x, float _y, const SpriteSheet *_spritesheet) :
Entity(_spritesheet), left_key(false), right_key(false), action_key(false) {
    x = _x;
    y = _y;
    xv = 0.0f;
    yv = 0.0f;
    sprite_id = 19;
    collideable = true;
}

void Player::jump() {
    switch(player_state) {
        case GROUND: player_state = JUMP_1_START; break;
        case JUMP_1: player_state = JUMP_2_START; break;
        default: {}
    }
}

void Player::handle_event(SDL_Event *event) {
    if(event->type == SDL_KEYDOWN || event->type == SDL_KEYUP) {
        bool keydown = event->type == SDL_KEYDOWN;
        switch(event->key.keysym.sym) {
            case SDLK_z:
            case SDLK_SPACE:
                {
                    if(keydown)
                        jump();
                    break;
                }
            case SDLK_d:
            case SDLK_RIGHT: right_key = keydown; break;
            case SDLK_a:
            case SDLK_LEFT: left_key = keydown; break;
            case SDLK_x: action_key = keydown; break;
            default: {}
        }
    }
}

bool Player::update() {
    const int old_y = y;
    const int old_x = x;

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
    } else if(y <= 0.0f) {
        player_state = GROUND;
        y = 0.0f;
    }

    if(right_key && !left_key) {
        xv = 2.0f;
    } else if(left_key && !right_key) {
        xv = -2.0f;
    } else {
        xv = 0.0f;
    }
    x += xv * state.fps.speed;

    return old_x != (int)x || old_y != (int)y;
}
