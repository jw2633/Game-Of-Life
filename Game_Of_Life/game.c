/*
 * Milestone3 game.c
 * Author: James Wang jw263
*/


#include <unistd.h>
#include <time.h>
#include "game.h"
#include "curses.h"
#include "well.h"

struct timespec req = {0};
int choice ;
int save = 0;

void initializeScreen() {
    // Initialize the screen for curses
    initscr();
    start_color();
    cbreak();
    keypad(stdscr, TRUE);
}

void startGame() {

    // Initialize the Screen
    initializeScreen();

    choice = welcome_message();
    // Initialize the Global 2D array
    initialize_array(choice);

    while(1) {
        mvprintw(21,75,"Press S or s to start        ");
        char key = getch();
        if(key == 's' || key == 'S')
                break;      
    }
    timeout(TIME_OUT);
    char ch ; 

    int loop = 1, quit_flag = 0;

    // Set sleep time to 150 ms
    req.tv_sec = 0;
    req.tv_nsec = 150000000L;

    while(loop) {
        // Print array
        display_array(stdscr);

        // Read the character
        ch = getch();

        switch (ch) {

            case 'q':
            case 'Q':
                quit();
                loop = 0;
                break;

            case 'P':
            case 'p':
                timeout(-1);
                quit_flag = pause2(stdscr);
                if(quit_flag == 1) {
                    quit();
                    loop = 0;
                }
                timeout(TIME_OUT);
                break;
            
            case 'r':
            case 'R':
                reset();
                break;

            case '+':
                increase_board_size();
                break;

            case '-':
                decrease_board_size();
                break;

            case '*':
                speed_up();
                break;

            case '/':
                speed_down();
                break;  

            case 'l':
            case 'L':
                timeout(-1);
                load_from_file(stdscr,1);
                timeout(TIME_OUT);
                break;

            case 'f':
            case 'F':
                // save content to a file
                save_to_file();
                break;  

            case 'g':
            case 'G':
                // save content to a file
            timeout(-1);
                printGNU(stdscr);
                timeout(TIME_OUT);
                break; 

            default:
                break;
        }
        // Update the array
        new_generation();

        //Sleep
        nanosleep (&req,(struct timespec *)NULL);
    }
    endwin();    
}

void quit() {
    GAME_OVER(stdscr);
    req.tv_sec = 2;
}

int pause2(WINDOW* w) {

    wclear(w);
    int ch;

    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);

    char menu[8][25] = {"Resume", "Reset","Pick a shape", "Save", "Load", "GNU", "Help", "Quit"};
    char item[7] = {'0'};

    int i;

    for( i=0; i<8; i++ ) {
        if( i == 0 ) {
            //attron(COLOR_PAIR(1));
            wattron( w, A_STANDOUT ); // highlights the first item.
            //attroff(COLOR_PAIR(1));
        }
        else {
            wattroff( w, A_STANDOUT );
        }
        //sprintf(item, "%-7s",  menu[i]);
        mvwprintw( w, i+1, 2, "%s", menu[i] );
    }

    wrefresh(w); // update the terminal screen


    i=0;
    int loopFlag = 1 ;
    while(loopFlag){ 
             ch = getch() ;
                // right pad with spaces to make the items appear with even width.
            
            mvwprintw( w, i+1, 2, "%s", menu[i] ); 
              // use a variable to increment or decrement the value based on the input.
            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? 7 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>7 ) ? 0 : i;
                            break;
                case 10:
                    //mvwprintw( w, 54, 22, "Enter pressed");
                    if (i != 6)
                        loopFlag = 0;
                    else {
                        help(stdscr);
                        wclear(w);
                    
                        int j = 0;
                        for( j=0; j<8; j++ ) {
                            if( j == 6 ) {
                                //attron(COLOR_PAIR(1));
                                wattron( w, A_STANDOUT ); // highlights the first item.
                                //attroff(COLOR_PAIR(1));
                            }
                            else {
                                wattroff( w, A_STANDOUT );
                            }
                            //sprintf(item, "%-7s",  menu[i]);
                            mvwprintw( w, j+1, 2, "%s", menu[j] );
                        }

                        wrefresh(w); // update the terminal screen                     

                    }
                    break;

                default:
                    mvwprintw( w, 54, 22, "%d", ch);
                    break;
            }

            // now highlight the next item in the list.
            attron(COLOR_PAIR(2)); 
            wattron( w, A_STANDOUT );
            
            mvwprintw( w, i+1, 2, "%s", menu[i]);
            attroff(COLOR_PAIR(2));
            wattroff( w, A_STANDOUT );
            wrefresh( w );
    }

    if (i == 0) {
        // Resume
        //return;
    }
    else if (i == 1) {
        //Reset
        reset();
    }
    else if (i == 2) {
        //Pick a Shape
        pick_shape(stdscr);
    } 
    else if (i == 3) {
        // Save
        save_to_file();
    }
    else if (i == 4) {
        // Load
         //mvwprintw( w, 21, 2, "inload");
        load_from_file(stdscr,2);
        //return 'l';
    }     
    else if (i == 5) {
        // GNU
        printGNU(stdscr);
    }
    else if (i == 6) {
        // Help
    }
    else {  // i = 7
        // Quit
        return 1;
    }
    return 0;
}

void reset() {
    initialize_array(choice);
    current_rows = 1000;
    current_cols = 1000;

    req.tv_sec = 0;
    req.tv_nsec = 150000000L;
}

void speed_up() {
    req.tv_sec /= 1.2;
    req.tv_nsec /= 1.2;
}

void speed_down() {
    req.tv_sec *= 1.2;
    req.tv_nsec *= 1.2;

    long temp = req.tv_nsec*1.2;

    if(temp > 888888888L) {
        req.tv_sec += 1;
        req.tv_nsec = temp - 888888888L;
    } 
}

void save_to_file() {
    save++;
    char file_name[100];
    int i,j;
    mkdir("./saves", 0777);   
    sprintf(file_name,"./saves/save_%d.life",save);
    FILE* fptr = fopen(file_name,"w");

    if(fptr == NULL){
        ;
    }

    else {
        for(i = 0; i < current_rows ; i++) {
            for (j = 0 ; j < current_cols ; j++) {
                int n ;//= array[i][j].present == LIVE ? 1 : 0;

                if(array[i][j].present == LIVE) {
                    n = 1;
                }
                else if(array[i][j].previous == LIVE)
                    n = 2;
                else
                    n = 3;

                fprintf(fptr,"%d ",n);
            }
            fprintf(fptr,"\n");
        }
    }
}

void load_from_file(WINDOW *win, int source) {
    wclear(win);
    int x, i, j;
    mkdir("./saves", 0777);
    mvprintw(10,2,"Enter the save number: ");
    scanw("%d",&x);
    //mvprintw(12,2,"x= %d",x);
    char file_name[100];
    sprintf(file_name,"./saves/save_%d.life",x); 
    FILE* fptr = fopen(file_name,"r");

    if(fptr == NULL){
        ;
    }

    else {

        for(i = 0; i < current_rows ; i++) {
            for (j = 0 ; j < current_cols ; j++) {
                int n;
                fscanf(fptr,"%d ",&n);
                //array[i][j].present = (n==1 ? LIVE : DEAD);  
                if(n == 1)
                      array[i][j].present = LIVE;
                else if(n == 2) {
                    array[i][j].previous = LIVE;
                    array[i][j].present = DEAD;
                }
                else {
                    array[i][j].present = array[i][j].previous = DEAD;            
                }
            }
        }
    }
    //wrefresh(win); 
}


void printGNU(WINDOW* win) {

    wclear(win);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(2));

    mvprintw( 13, 75,"#################  #                       # #               #");
    mvprintw( 14, 75,"#                  # #                     # #               #");
    mvprintw( 15, 75,"#                  #   #                   # #               #");
    mvprintw( 16, 75,"#                  #     #                 # #               #");
    mvprintw( 17, 75,"#                  #       #               # #               #");
    mvprintw( 18, 75,"#                  #         #             # #               #");
    mvprintw( 19, 75,"#                  #           #           # #               #");
    mvprintw( 20, 75,"#       #########  #             #         # #               #");
    mvprintw( 21, 75,"#               #  #               #       # #               #");
    mvprintw( 22, 75,"#               #  #                 #     # #               #");
    mvprintw( 23, 75,"#               #  #                   #   # #               #");
    mvprintw( 24, 75,"#               #  #                     # # #               #");
    mvprintw( 25, 75,"#################  #                       # #################");
    attroff(COLOR_PAIR(2));
    wrefresh(win);
    int ch = getch();
}

void help(WINDOW* win) {
    wclear(win);
    mvprintw(12,75,"Q/q for Quit");
    mvprintw(13,75,"P/p for Pause");
    mvprintw(14,75,"R/r for reset");
    mvprintw(15,75,"F/f to save");
    mvprintw(16,75,"L/l to load");
    mvprintw(17,75,"+ to increase board size");
    mvprintw(18,75,"- to decrease board size");
    mvprintw(19,75,"* to speed up");
    mvprintw(20,75,"/ to speed down");
    mvprintw(21,75,"G/g for GNU");

    wrefresh(win);
    int ch = getch();

}

