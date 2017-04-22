// sample from https://wiki.libsdl.org/SDL_RenderCopy
#include "SDL2/SDL.h"
#include "globals.hpp"
#include "state.hpp"

game_state_t _game_state;

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
    window = SDL_CreateWindow("a small world", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 360, 240, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // setup background
    background_map_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 720, 480);
    SDL_SetRenderTarget(renderer, background_map_tex);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x20, 0x88, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    // setup player - white square with black outline
    const int player_height = 60;
    const int player_width = 40;

    player_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, player_height, player_width);
    SDL_SetRenderTarget(renderer, player_tex);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderDrawRect(renderer, NULL); // draws a white outline
    SDL_SetRenderTarget(renderer, NULL);

    // this is where we draw everything to, which will eventually be scaled to the full screen
    // we will work in 360x240 pixel range
    merged_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 360, 240);

    SDL_Rect player_pos_rect;
    player_pos_rect.h = player_height + 1; // dunno why i have to extend this by 1
    player_pos_rect.w = player_width + 1;

    player_pos_rect.y = 240 - player_height;
    player_pos_rect.x = 130;

    int anim_counter = 0;
    const int anim_frames = 80;

    SDL_Event event;
    int t_start;
    while(true) {
        t_start = SDL_GetTicks();

        SDL_PollEvent(&event);
        if(event.type == SDL_QUIT)
            break;

        {
            // render

            // draw everything on merged_tex then copy to render buffer
            SDL_SetRenderTarget(renderer, merged_tex);
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);

            SDL_Rect player_anim_rect = player_pos_rect;

            player_anim_rect.y -= (anim_counter % anim_frames); // 0 x 0 is top left
            SDL_RenderCopy(renderer, background_map_tex, NULL, NULL);
            SDL_RenderCopy(renderer, player_tex, NULL, &player_anim_rect);

            SDL_SetRenderTarget(renderer, NULL);
            SDL_RenderCopy(renderer, merged_tex, NULL, NULL);
            SDL_RenderPresent(renderer);
        }

        SDL_Delay(16 - (SDL_GetTicks() - t_start));
        anim_counter++;
    }

    SDL_DestroyTexture(background_map_tex);
    SDL_DestroyTexture(player_tex);
    SDL_DestroyTexture(merged_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
