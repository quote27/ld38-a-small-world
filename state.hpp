#pragma once
#include "globals.hpp"

// Taken from sdl tutorial.
struct fps_t {
    int old, last, fps, frames;
    float speed;

    fps_t() : old(0), last(0), fps(0), frames(0), speed(0.f) {}
    void update();
};

class State {
    public:
        fps_t fps;

        State();

        void update();
        void handle_event(SDL_Event *event);
};
