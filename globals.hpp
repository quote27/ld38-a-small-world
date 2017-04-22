#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

static const uint32_t SCREEN_WIDTH = 320;
static const uint32_t SCREEN_HEIGHT = 240;

extern SDL_Surface* screen;
enum game_state_t { LOADING, START_SCREEN, IN_GAME, SCORE_SCREEN, QUIT };
extern game_state_t _game_state;

static const float gravity = .25;
static const float epsilon = 1e-6;

class State;
extern State state;
