/*
 * Milestone3 game.h
 * Author: James Wang jw263
*/


#ifndef _GAME
#define _GAME
#include "curses.h"
void startGame();
void quit();
int pause2(WINDOW* w);
void printGNU(WINDOW* w);
void reset();
void speed_up();
void speed_down();
void save_to_file();
void load_from_file(WINDOW *win, int source);
void help(WINDOW* win);
#endif
/*

make clean 
rm -f *~ core /*~ 
rm -f  game_of_life
rm -f *.o

 make
gcc -c -o main.o main.c -I../include -g -O0
gcc -c -o cell.o cell.c -I../include -g -O0
gcc -c -o game.o game.c -I../include -g -O0
gcc -c -o well.o well.c -I../include -g -O0
gcc -c -o key.o key.c -I../include -g -O0
gcc -o game_of_life main.o cell.o game.o well.o key.o -I../include -g -O0 -lncurses

*/

/*


wrefresh(win);

*/
