// sample from https://wiki.libsdl.org/SDL_RenderCopy
#include "globals.hpp"
#include "state.hpp"
#include "spritesheet.hpp"
#include "player.hpp"

game_state_t _game_state;
State state;

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
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SpriteSheet* spritesheet = new SpriteSheet(renderer, "spritesheet.png");

    // setup background
    background_map_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderTarget(renderer, background_map_tex);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x20, 0x88, 0xff);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    // setup player - white square with black outline
    const int player_height = 80;
    const int player_width = 80;

    player_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                   SDL_TEXTUREACCESS_TARGET, player_height, player_width);
    SDL_SetTextureBlendMode(player_tex, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, player_tex);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    // draw everything to a single texture, then have the renderer scale it to match
    // the window size
    merged_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);

    Player player(100, 0, spritesheet);

    SDL_Event event;
    int frame_counter = 0;
    int t_start;
    while(_game_state != GAME_QUIT) {
        t_start = SDL_GetTicks();

        while(SDL_PollEvent(&event)) {
            state.handle_event(&event);
            player.handle_event(&event);
        }

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
            player.draw();

            SDL_SetRenderTarget(renderer, NULL);
            //SDL_RenderCopy(renderer, merged_tex, NULL, NULL);
            // TODO: if we do this, we can pretend that the bottom left is 0,0
            // however we'll have to flip all the sprites as we render them
            // this might be ok as spritesheet will handle that
            SDL_RenderCopyEx(renderer, merged_tex, NULL, NULL, 0.0, NULL, SDL_FLIP_VERTICAL);
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
