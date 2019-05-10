/*
 * Milestone3 cell.c
 * Author: James Wang jw263
*/


#include "cell.h"
#include "well.h"
#include<ncurses.h>

// Create a new cell and return it
cell_t newCell() {
    cell_t new_cell;

    new_cell.previous = UNKNOWN;
    new_cell.present = UNKNOWN;
    new_cell.next = UNKNOWN;

    return new_cell;
}

//Get the next generation of cells
void new_generation() {
    int i;
    int j;
    for(i = 0 ; i < current_rows ; i++) {
        for (j = 0 ; j < current_cols ; j++) {

            // Count the number of LIVE cells surrounding array[i][j]
            int sum = neighbour_live_cells(i,j);

            // Update the next state of array[i][j] following the 4 rules
            update_next_state(i,j,sum);
        }
    }
    for(i = 0 ; i < current_rows ; i++) {
        for(j = 0; j < current_cols ; j++) {
            array[i][j].present = array[i][j].next;
        }
    }

}

// Find the neighboring Live Cells
int neighbour_live_cells (int i, int j) {

      int sum = 0;
      int row = i, col = j;
      /*
      // Neighbours in the next row
      if(row+1 < current_rows) {
        if(col + 1 < current_cols)
            sum += (array[row+1][col+1].present == LIVE ? 1 : 0);

        sum += (array[row+1][col].present == LIVE ? 1 : 0);
        
        if(col - 1 >= 0)
            sum += (array[row+1][col-1].present == LIVE ? 1 : 0);
      }

      // Neighbours in the same row
      if(col + 1 < current_cols){
        sum += (array[row][col+1].present == LIVE ? 1 : 0);
      }
      if(col - 1 >= 0){
        sum += (array[row][col-1].present == LIVE ? 1 : 0);
      }

      // Neighbours in the previous row
      if(row-1 >= 0) {
        if(col + 1 < current_cols)
            sum += (array[row-1][col+1].present == LIVE ? 1 : 0);

        sum += (array[row-1][col].present == LIVE ? 1 : 0);

        if(col - 1 >= 0)
            sum += (array[row-1][col-1].present == LIVE ? 1 : 0);

      }  

      */
    sum = 
    (array[(i - 1 + COLS) % COLS][j].present == LIVE ? 1 : 0)   +

    (array[(i - 1 + COLS) % COLS][(j - 1 + LINES) % LINES].present == LIVE ? 1 : 0)   +
    (array[(i - 1 + COLS) % COLS][(j + 1) % LINES].present == LIVE ? 1 : 0)   +
    (array[(i + 1) % COLS][j].present == LIVE ? 1 : 0)    +
    (array[(i + 1) % COLS][(j - 1 + LINES) % LINES].present == LIVE ? 1 : 0)  +
    (array[(i + 1) % COLS][(j + 1) % LINES].present == LIVE ? 1 : 0)  +
    (array[i][(j - 1 + LINES) % LINES].present == LIVE ? 1 : 0)   +
    (array[i][(j + 1) % LINES].present == LIVE ? 1 : 0);

  return sum;

}

void update_next_state(int row, int col, int sum) {
      
      // 4 Different cases to update the cell

      if (array[row][col].present == LIVE) {
          if (sum < 2 || sum > 3) {
              array[row][col].next = UNKNOWN;
          }
          else {
              array[row][col].next = LIVE;
              array[row][col].previous = LIVE;
          }
      }
      else {
          if(sum == 3){
            array[row][col].next = LIVE;
            array[row][col].previous = LIVE;
          }
          else  
            array[row][col].next = UNKNOWN;  
      }
}

void display_cell (int row, int col)
{
  if (array[row][col].present == LIVE)
    mvprintw(row, col, "%c", '$');
  else
    mvprintw(row, col, " ");
}

// displaj all the cells
void display_cells ()
{
    int i, j;
  for (i = 0; i < current_rows; i++)
    for (j = 0; j < current_cols; j++)
      display_cell(i, j);
}
