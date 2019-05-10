/*
 * Milestone3 key.c
 * Author: James Wang jw263
*/


#include<curses.h>

char getKey() {
	char ch = getch();
	return ch;
}
