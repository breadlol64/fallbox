#include "game.h"

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>

struct Game init_game() {
    struct Game game = {0};

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        game.ok = 0;
        return game;
    }

    game.window = SDL_CreateWindow("Fallbox 0.1.0", 800, 600, 0);
    if (!game.window) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        SDL_Quit();
        game.ok = 0;
        return game;
    }

    game.renderer = SDL_CreateRenderer(game.window, NULL);
    if (!game.renderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        SDL_DestroyWindow(game.window);
        SDL_Quit();
        game.ok = 0;
        return game;
    }
    SDL_SetRenderVSync(game.renderer, 1);

    game.ok = 1;
    return game;
}
