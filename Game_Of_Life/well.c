/*
 * Milestone3 well.c
 * Author: James Wang jw263
*/


#include "well.h"
#include "cell.h"
#include <time.h>

cell_t array[MAXROWS][MAXCOLS];

int current_rows = 300;
int current_cols = 300;

void still_life() {
    // still life
	array[5][5].present = LIVE;
	array[5][6].present = LIVE;
	array[6][5].present = LIVE;
	array[6][6].present = LIVE;

        array[5][5].previous = LIVE;
    array[5][6].previous = LIVE;
    array[6][5].previous = LIVE;
    array[6][6].previous = LIVE;

}

void oscillator() {
    // oscillator
	array[20][20].present = LIVE;
	array[20][21].present = LIVE;
	array[20][22].present = LIVE;

    array[20][20].previous = LIVE;
    array[20][21].previous = LIVE;
    array[20][22].previous = LIVE;
}

void glider() {
    // glider
	array[20][5].present = LIVE;
	array[20][6].present = LIVE;
	array[20][7].present = LIVE;
	array[21][7].present = LIVE;
	array[22][6].present = LIVE;


    array[20][5].previous = LIVE;
    array[20][6].previous = LIVE;
    array[20][7].previous = LIVE;
    array[21][7].previous = LIVE;
    array[22][6].previous = LIVE;
}

void inverted_u() {
    array[39][15].present = LIVE;
	array[40][15].present = LIVE;
	array[41][15].present = LIVE;
	array[39][16].present = LIVE;
	array[39][17].present = LIVE;
	array[41][16].present = LIVE;
	array[41][17].present = LIVE;

    array[39][15].previous = LIVE;
    array[40][15].previous = LIVE;
    array[41][15].previous = LIVE;
    array[39][16].previous = LIVE;
    array[39][17].previous = LIVE;
    array[41][16].previous = LIVE;
    array[41][17].previous = LIVE;

}

void initialize_array(int choice) {

    int i;
    int j;

    for(i = 0 ; i < MAXROWS ; i++ ) {
        for(j = 0 ; j < MAXCOLS ; j++) {
        cell_t cell_ = newCell();
        array[i][j] = cell_;
        }
    }

    // Pre defined state
    if(choice == 1) {
        still_life();glider();oscillator();inverted_u();
    }
    else {  //random state
        srand(time(NULL));
        int n = rand()%4;
        if(n == 0)
            still_life();
        else if(n == 1) 
            glider();
        else if (n == 2)
            oscillator();
        else
            inverted_u();
    }
}

void pick_shape(WINDOW* win) {
    wclear(win);
    int x;
    mvprintw(20,75,"Enter a Shape: ");
    scanw("%d",&x);

    wrefresh(win);
}

void display_array(WINDOW *win) {
	int i, j;
	wclear(win);

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);

	for(i = 0; i <= current_rows; ++i) 
		for(j = 0;j <= current_cols; ++j) 
			if(array[i][j].present == LIVE) {
                attron(COLOR_PAIR(1));
				mvwaddch(win, j, i, '#');
                attroff(COLOR_PAIR(1));
            }
            else if(array[i][j].present == DEAD){
                attron(COLOR_PAIR(2));
                mvwaddch(win, j, i, '#');
                attroff(COLOR_PAIR(2));
            }
            else if(array[i][j].previous == LIVE) {
                attron(COLOR_PAIR(3));
                mvwaddch(win, j, i, '#');
                attroff(COLOR_PAIR(2));                
            }
	wrefresh(win);
}

void increase_board_size() {
    current_rows += 2;
    current_cols += 2;

    if(current_rows > MAXROWS)
        current_rows = MAXROWS;
    if(current_cols > MAXCOLS)
        current_cols = MAXCOLS;
}

void decrease_board_size() {
    current_rows -= 2;
    current_cols -= 2;

    if(current_rows < 0)
        current_rows = 0;
    if(current_cols < 0)
        current_cols = 0;    
}

int welcome_message() {
        int x;
		mvprintw(15,75,"WELCOME TO THE GAME OF LIFE");
        mvprintw(17,75,"James Wang");
		mvprintw(18,75,"Press 1 for Starting with a pre defined shape");
        mvprintw(19,75,"Press 2 for Starting with a random shape");
        mvprintw(20,75,"Enter your choice: ");
        scanw("%d",&x);

        return x;
} 	

void GAME_OVER(WINDOW *win){
    wclear(win);
    timeout(-1);
	mvprintw(15,95,"All life has been terminated. Why did you have to do this?... (Press any key to exit)");
    int ch = getch();
    timeout(1);
	wrefresh(win); 
}
