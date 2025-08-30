#ifndef CELL_H
#define CELL_H
#include <SDL3/SDL_render.h>

enum CellType {
    AIR,
    SAND,
    STONE,
    WATER
};

struct Cell {
    // int x;
    // int y;
    int type;
};

void draw_cell(SDL_Renderer* renderer, int x, int y);

#endif //CELL_H
