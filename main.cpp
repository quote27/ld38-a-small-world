// started with sample from https://wiki.libsdl.org/SDL_RenderCopy
#include<vector>
#include "globals.hpp"
#include "state.hpp"
#include "spritesheet.hpp"
#include "player.hpp"
#include "map.hpp"
#include "camera.hpp"
#include "interactable.hpp"

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

    // init window and renderer
    window = SDL_CreateWindow("a small world", SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    const SpriteSheet* spritesheet = new SpriteSheet(renderer, "spritesheet.png");
    Map* map = new Map(renderer, spritesheet, 18, 32);
    map->tiles[0] = std::vector<int>(map->tiles[0].size(), 123);
    map->compose();

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

    Player player(100, 0, spritesheet);
    Camera camera(renderer, &player, map, 360, 640);

    Interactable bug(200, 20, spritesheet, 321, true);


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
            bug.update();
        }

        {   // render
            // draw everything on camera viewport then copy to render buffer
            SDL_SetRenderTarget(renderer, camera.viewport);
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
            SDL_RenderClear(renderer);

            // background first
            SDL_RenderCopy(renderer, background_map_tex, NULL, NULL);

            // entities next
            map->draw();
            player.draw();
            bug.draw();
            camera.draw(); // Always last.
        }

        int32_t delay = 16 - (SDL_GetTicks() - t_start);
        SDL_Delay(delay < 0 ? 0 : delay);
        frame_counter++;
    }

    SDL_DestroyTexture(background_map_tex);
    SDL_DestroyTexture(player_tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
