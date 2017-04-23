#include "player.hpp"
#include "state.hpp"
#include "spritesheet.hpp"

Player::Player(float x, float y, SDL_Renderer *renderer, const SpriteSheet *spritesheet)
    : x(x), y(y), xv(0.0f), yv(0.0f), spritesheet(spritesheet) {
    sprite_id = 19;

    tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, h, w);
    SDL_SetRenderTarget(renderer, tex);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderDrawRect(renderer, NULL); // draws a white outline
    SDL_SetRenderTarget(renderer, NULL);
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

void Player::draw(SDL_Renderer *renderer) {
    // this assumes renderer is pointing to the correct target
    SDL_Rect r = {(int)x, (int)y, (int)w+1, (int)h};

    // this will call spritesheet->draw eventually
    spritesheet->render(sprite_id, r);
}
