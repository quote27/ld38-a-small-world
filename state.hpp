#pragma once
#include "globals.hpp"

enum player_state {
    GROUND,
    JUMP_1_START,
    JUMP_1,
    JUMP_2_START,
    JUMP_2,
    SLIDE,
    HOVER,
    HOVER_FALL
};

                                          // 200ms is threshold for 'tap'
const static unsigned tap_threshold = 11; // 10 frames * 16ms/frame
enum keypress_length { NONE, TAP, HOLD };

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
        player_state ps;
        bool button_pressed;
        // Count num of frames to move between 'tap' and 'hold' modes.
        unsigned button_count;
        keypress_length button_state;
        long long frame;
        int hold_time;

        State();

        void update();
        bool active_frame();
        void tap();
        void hold();
        void release();
        void keydown(SDL_Keycode sym, uint16_t mod);
};
