#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const uint32_t SCREEN_WIDTH = 360;
static const uint32_t SCREEN_HEIGHT = 240;

static const uint32_t WINDOW_WIDTH = 1280;
static const uint32_t WINDOW_HEIGHT = 720;

static const uint32_t SPRITE_SIZE = 40;

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
