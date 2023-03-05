#include <string.h>
#include "msnake.h"

// In this function, we will start the ncurses subsystem and configure parameters.
void initGame() {
    initscr();
    confScreen();
    if (getmaxy(stdscr) < MAP_H+4 || getmaxx(stdscr) < MAP_L+2) {
        endwin();
        printf("Error: Your terminal is too small!\n");
        exit(2);
    }
    // Configure the ncurses color subsystem
    start_color();
    init_pair(WALL_PAIR, COLOR_WHITE, COLOR_WHITE);
    init_pair(SNAKE_PAIR, COLOR_CYAN, COLOR_BLACK);
    init_pair(FOOD_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(MSG_PAIR, COLOR_CYAN, COLOR_BLACK);
    // Copyright
    attron(COLOR_PAIR(MSG_PAIR));
    mvprintw(START_Y-2, START_X-1, "MSNAKE V1.0");
    mvprintw(START_Y-2, START_X+MAP_L-11, "By MichaelXu");
    attroff(COLOR_PAIR(MSG_PAIR));
    // Draw framework, draw walls
    for (int i = 0; i < (MAP_L+2)*(MAP_H+2); ++i) {
        int x = START_X-1 + i % (MAP_L+2), y = START_Y-1 + i / (MAP_L+2);
        if (x==START_X-1||x==START_X+MAP_L||y==START_Y-1||y==START_Y+MAP_H) drawBlock(x, y, 0, 1);
    }
}

void repaintScreen() {
    for (int i = 0; i < MAP_L*MAP_H; ++i) {
        mvaddch(DEST_Y(i), DEST_X(i), ' ');
    }
    refresh();
}

int showMenu() {
    attron(COLOR_PAIR(MSG_PAIR));
    attron(A_BOLD);
    mvprintw(MID_Y-8, MID_X-18, "             _____             _        ");
    mvprintw(MID_Y-7, MID_X-18, "            / ____|           | |       ");
    mvprintw(MID_Y-6, MID_X-18, "  _ __ ___ | (___  _ __   __ _| | _____ ");
    mvprintw(MID_Y-5, MID_X-18, " | '_ ` _ \\ \\___ \\| '_ \\ / _` | |/ / _ \\");
    mvprintw(MID_Y-4, MID_X-18, " | | | | | |____) | | | | (_| |   <  __/");
    mvprintw(MID_Y-3, MID_X-18, " |_| |_| |_|_____/|_| |_|\\__,_|_|\\_\\___|");
    mvprintw(MID_Y-2, MID_X-18, "                                        ");
    mvprintw(MID_Y-1, MID_X-18, "+----------CHOOSE YOUR OPTION----------+");
    mvprintw(MID_Y+0, MID_X-18, "|                                      |");
    mvprintw(MID_Y+1, MID_X-18, "|         1. PLAY NOW (y/Y)            |");
    mvprintw(MID_Y+2, MID_X-18, "|         2. SHOW HISTORY (t/T)        |");
    mvprintw(MID_Y+3, MID_X-18, "|         3. EXIT NOW (q/Q)            |");
    mvprintw(MID_Y+4, MID_X-18, "|                                      |");
    mvprintw(MID_Y+5, MID_X-18, "+--------------------------------------+");
    refresh();
    int option = getch();
    attroff(COLOR_PAIR(MSG_PAIR));
    attroff(A_BOLD);
    if (option == 'y' || option == 'Y') return 1;
    else if (option == 't' || option == 'T') return 2;
    else if (option == 'q' || option == 'Q') return 3;
    else return 4;
}

void showHistory() {
    struct ScoreData * list = getData();
    attron(COLOR_PAIR(MSG_PAIR));
    attron(A_BOLD);
    mvprintw(MID_Y-7, MID_X-22, "+-------------- PLAYER HISTORY --------------+");
    mvprintw(MID_Y-6, MID_X-22, "|                                            |");
    for (int i = 0; i < 10; ++i) {
        int sc = list[9-i].score;
        if (sc != 0) {
            mvprintw(MID_Y-5+i, MID_X-22, "|    %2d  %s     %8d   |", i+1, list[9-i].game_time, sc);
        } else {
            mvprintw(MID_Y-5+i, MID_X-22, "|                                            |");
        }
    }
    mvprintw(MID_Y+5, MID_X-22, "|                                            |");
    mvprintw(MID_Y+6, MID_X-22, "+--------------------------------------------+");
    attroff(A_BOLD);
    attroff(COLOR_PAIR(MSG_PAIR));
    getch();
    free(list);
    repaintScreen();
}

void confScreen() {
    noecho();
    cbreak();
    keypad(stdscr,TRUE);
    curs_set(0); // curs_set(0) is to hide the cursor
}