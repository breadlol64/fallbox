#ifndef GAME_H
#define GAME_H
#include <SDL3/SDL_render.h>

struct Game {
    SDL_Renderer* renderer;
    SDL_Window* window;
    int ok;
};

struct Game init_game();

#endif //GAME_H
