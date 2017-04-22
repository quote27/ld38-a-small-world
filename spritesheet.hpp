#include "globals.hpp"

class SpriteSheet {
  public:
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int rows;
    int columns;
    uint32_t margin;

    SpriteSheet(SDL_Renderer* _renderer, const char* file_path, uint32_t _margin = 2);
    void render(uint32_t id, SDL_Rect dest);

  private:
    SDL_Rect buffer;
};
