// sample from https://wiki.libsdl.org/SDL_RenderCopy
#include "globals.hpp"
#include "state.hpp"
#include "player.hpp"

game_state_t _game_state;
State state;

void handle_event(SDL_Event *e) {
	switch(e->type) {
		case SDL_KEYDOWN: { state.keydown(e->key.keysym.sym, e->key.keysym.mod);  break; }
		// case SDL_KEYUP: { state.keyup(e->key.keysym.sym, e->key.keysym.mod, e->key.keysym.scancode); break; }
		case SDL_QUIT: _game_state = GAME_QUIT;
	}
}

int main(int argc, char *argv[])
{

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        return 1;
    }


    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* background_map_tex;
    SDL_Texture* player_tex;
    SDL_Texture* merged_tex;

    // init window and renderer
    window = SDL_CreateWindow("a small world", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // setup background
    background_map_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderTarget(renderer, background_map_tex);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x20, 0x88, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    // setup player - white square with black outline
    const int player_height = 60;
    const int player_width = 40;

    player_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, player_height, player_width);
    SDL_SetRenderTarget(renderer, player_tex);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderDrawRect(renderer, NULL); // draws a white outline
    SDL_SetRenderTarget(renderer, NULL);

    // draw everything to a single texture, then have the renderer scale it to match
    // the window size
    merged_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    Player player(100, 200, renderer);

    SDL_Event event;
    int frame_counter = 0;
    int t_start;
    while(_game_state != GAME_QUIT) {
        t_start = SDL_GetTicks();

        while(SDL_PollEvent(&event))
            handle_event(&event);

        if(_game_state == GAME_QUIT)
            break;

        {
            // update
            state.update();
            player.update();
        }

        {
            // render

            // draw everything on merged_tex then copy to render buffer
            SDL_SetRenderTarget(renderer, merged_tex);
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);

            // background first
            SDL_RenderCopy(renderer, background_map_tex, NULL, NULL);

            // entities next
            player.draw(renderer);

            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, merged_tex, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        int32_t delay = 16 - (SDL_GetTicks() - t_start);
        SDL_Delay(delay < 0 ? 0 : delay);
        frame_counter++;
    }

    SDL_DestroyTexture(background_map_tex);
    SDL_DestroyTexture(player_tex);
    SDL_DestroyTexture(merged_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
