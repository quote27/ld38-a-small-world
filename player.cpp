#include "player.hpp"
#include "state.hpp"
#include "spritesheet.hpp"

Player::Player(float _x, float _y, const SpriteSheet *_spritesheet) :
    Entity(_spritesheet), left_key(false), right_key(false), action_key(false) {
    init(_x, _y, 0.0f, 0.0f, 19, true);
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
            case SDLK_RIGHT: right_key = keydown; break;
            case SDLK_LEFT: left_key = keydown; break;
            case SDLK_x: action_key = keydown; break;
            default: {}
        }
    }
}

bool Player::update() {
    old_x = x;
    old_y = y;
    old_xv = xv;
    old_yv = yv;

    switch(player_state) {
        case GROUND: yv = 0; break; //do nothing, y-axis doesnt change - TODO: animation change
        case JUMP_2_START:
        case JUMP_1_START: yv = 8; break; //vel[1] = 1; break; //add 'jump' to velocity
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

    return (int)old_x != (int)x || (int)old_y != (int)y;
}

void Player::undo() {
    x = old_x;
    y = old_y;
    xv = old_xv;
    yv = old_yv;
}

void Player::resolve_collision(const Entity *other) {

}
