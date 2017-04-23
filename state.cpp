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

State::State() { }

void State::update() {
    fps.update();
}

void State::handle_event(SDL_Event *event) {
    switch(event->type) {
        case SDL_KEYDOWN:
            {
                switch(event->key.keysym.sym) {
                    case SDLK_q: _game_state = GAME_QUIT; break;
                    default: {}
                }
                break;
            }
        case SDL_QUIT: _game_state = GAME_QUIT; break;
        default: {}
    }

}
