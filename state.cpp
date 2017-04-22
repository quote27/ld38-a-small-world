#include "state.hpp"
#include "globals.hpp"

void fps_t::update() {
    int t = SDL_GetTicks();
    if (old+1000 < t) { // Update frame per second metric.
        old = t;
        fps = frames;
        frames = 0;
    }
    speed = ((t-last)/1000.f) * 60.f; // Target fps.
    last = t;
    frames++;
}

State::State() {
    //set everything to 0
    button_pressed = false;
    button_count = 0;
    button_state = NONE;
    frame = 0;
    hold_time = 0;
}

void State::update() {
    fps.update();
    if(button_pressed) {
        if(++button_count > tap_threshold) {
            button_state = HOLD;
            hold();
        }
    }
    frame++;
}

void State::tap() {
    switch(ps) {
        case GROUND: ps = JUMP_1_START; break;
        case JUMP_1: ps = JUMP_2_START; break;
        default: {}
    }
}

void State::hold() {
    switch(ps) {
        case GROUND: ps = SLIDE; break;
        case JUMP_1:
        case JUMP_2: ps = HOVER; break;
        default: {}
    }
}
void State::release() {
    switch(ps) {
        case SLIDE: ps = GROUND; break;
        case HOVER: ps = HOVER_FALL; break;
        default: {}
    }
}

void State::keydown(SDL_Keycode sym, SDL_Keymod mod, Uint16 unicode) {
    switch(sym) {
        case SDLK_z: tap(); break;
        case SDLK_q: _game_state = QUIT; break;
        default: {}
    }
}
