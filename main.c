#include <stdio.h>
#include <SDL3/SDL.h>
#include "cell.h"
#include "game.h"


int main(void) {
    struct Game game = init_game();
    if (!game.ok) {
        return 1;
    }

    struct Cell cells[600][800] = {0};
    struct Cell next_cells[600][800] = {0};

    struct Cell sand_cell = {SAND};
    struct Cell stone_cell = {STONE};
    struct Cell air_cell = {AIR};

    cells[300][400] = sand_cell;
    for (int x = 0; x < 400; x++) {
        next_cells[500][200+x] = stone_cell;
    }

    int selected_cell_type = SAND;

    SDL_Event event;
    int running = 1;
    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_EVENT_QUIT:
                    running = 0;
                    break;
                case SDL_EVENT_KEY_DOWN:
                    switch (event.key.key) {
                        case SDLK_1:
                            selected_cell_type = SAND;
                            break;
                        case SDLK_2:
                            selected_cell_type = STONE;
                            break;
                        default: ;
                    }
                    break;
                default: ;
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game.renderer);

        float mouse_x, mouse_y;
        SDL_MouseButtonFlags buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

        if (buttons & SDL_BUTTON_LMASK) {  // left mouse button held
            int x = (int)mouse_x;
            int y = (int)mouse_y;

            if (y >= 0 && y < 600 && x >= 0 && x < 800) {
                struct Cell cell = {selected_cell_type};
                next_cells[y][x] = cell;
            }
        }

        for (int y = 599; y >= 0; y--) {
            for (int x = 0; x < 800; x++) {
                struct Cell cell = cells[y][x];

                switch (cell.type) {
                    case AIR:
                        continue;
                    case SAND:
                        if (cells[y+1][x].type == AIR) {
                            next_cells[y+1][x] = cell;
                            next_cells[y][x] = air_cell;
                        } else if (cells[y+1][x+1].type == AIR) {
                            next_cells[y+1][x+1] = cell;
                            next_cells[y][x] = air_cell;
                        } else if (cells[y+1][x-1].type == AIR) {
                            next_cells[y+1][x-1] = cell;
                            next_cells[y][x] = air_cell;
                        }
                        break;
                    default: ;
                }

                draw_cell(game.renderer, x, y);
            }
        }

        SDL_RenderPresent(game.renderer);

        memcpy(cells, next_cells, sizeof(cells));
    }

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();
    return 0;
}
