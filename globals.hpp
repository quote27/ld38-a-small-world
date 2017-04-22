#pragma once
#include <SDL2/SDL.h>
#include <memory>

using namespace std;

static const uint32_t SCREEN_WIDTH = 360;
static const uint32_t SCREEN_HEIGHT = 240;

enum game_state_t {
    LOADING,
    START_SCREEN,
    IN_GAME,
    SCORE_SCREEN,
    GAME_QUIT
};
extern game_state_t _game_state;

static const float gravity = .25;
static const float epsilon = 1e-6;

class State;
extern State state;
