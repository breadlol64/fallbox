#include "cell.h"

void draw_cell(SDL_Renderer* renderer, int x, int y) {
    // printf("Drawing cell %d at x:%d y:%d\n", cells[y][x].type, x, y);
    SDL_FRect rect = { x, y, 1, 1 };
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
    // SDL_RenderPoint(renderer, x, y);
}
