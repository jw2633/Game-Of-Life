/*
 * Milestone3 well.h
 * Author: James Wang jw263
*/


#ifndef _WELL
#define _WELL

#include "cell.h"
#include <curses.h>

#define MAXROWS 10000
#define MAXCOLS 10000
#define TIME_OUT  300

extern cell_t array[MAXROWS][MAXCOLS];
extern int current_rows;
extern int current_cols;

void display_array(WINDOW *win);
int welcome_message(); 	
void GAME_OVER(WINDOW *win);
void initialize_array(int choice);
void pick_shape(WINDOW* win);
void increase_board_size();
void decrease_board_size();

#endif
