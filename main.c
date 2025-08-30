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
    int brush_size = 2;

    Uint64 start_time = SDL_GetPerformanceCounter();

    SDL_Event event;
    int running = 1;
    while (running) {
        Uint64 current_frame_start = SDL_GetPerformanceCounter();
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
                case SDL_EVENT_MOUSE_WHEEL:
                    if (!(brush_size == 0 && event.wheel.integer_y < 0)) brush_size += event.wheel.integer_y;
                    break;
                default: ;
            }
        }

        SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(game.renderer);

        float mouse_x, mouse_y;
        SDL_MouseButtonFlags buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

        if (buttons & SDL_BUTTON_LMASK) {  // left mouse button held
            int mx = (int)mouse_x;
            int my = (int)mouse_y;

            if (my >= 0 && my < 600 && mx >= 0 && mx < 800) {
                struct Cell cell = {selected_cell_type};
                for (int x = 0; x < brush_size; x++) {
                    for (int y = 0; y < brush_size; y++) {
                        next_cells[y+my][x+mx] = cell;
                    }
                }
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

        Uint64 current_frame_end = SDL_GetPerformanceCounter();
        float elapsed_seconds = (float)(current_frame_end - current_frame_start) / (float)SDL_GetPerformanceFrequency();

        if (elapsed_seconds > 0) {
            float fps = 1.0f / elapsed_seconds;
            printf("\rFPS: %f | Brush size: %d | Selected cell: %d", fps, brush_size, selected_cell_type);
            fflush(stdout);
        }
    }

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();
    return 0;
}
