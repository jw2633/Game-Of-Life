/*
 * Milestone3 cell.h
 * Author: James Wang jw263
*/


#ifndef _CELL
#define _CELL

typedef enum cellState {
    DEAD = 0,
    LIVE = 1,
    UNKNOWN = -1,
}
cell_state_t;

typedef struct cell {
    cell_state_t previous;
    cell_state_t present;
    cell_state_t next;
}
cell_t;

cell_t newCell();
void new_generation();
void update_next_state(int row, int col, int sum);

#endif
