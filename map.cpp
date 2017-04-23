#include "map.hpp"

Map::Map(SDL_Renderer *renderer, const SpriteSheet *spritesheet, int rows, int columns) :
    rows(rows),
    columns(columns),
    renderer(renderer),
    spritesheet(spritesheet)
{
    tiles = std::vector<std::vector<int>>(rows, std::vector<int>(columns, BLANK));
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET,
            columns * spritesheet->cwidth,
            rows * spritesheet->cheight);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    compose();
};

void Map::compose() {
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; col++) {
            SDL_Rect buffer;
            buffer.x = spritesheet->cwidth * col;
            buffer.y = spritesheet->cheight * row;
            buffer.h = spritesheet->cheight;
            buffer.w = spritesheet->cwidth;

            spritesheet->render(tiles[row][col], buffer);
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
}

void Map::draw() {
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}
