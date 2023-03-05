#ifndef MSNAKE_SNAKE_MAIN_H_
#define MSNAKE_SNAKE_MAIN_H_

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "msnake.h"

#define MAP_H 20
#define MAP_L 72
#define FPS 4

#define WALL_PAIR 1
#define SNAKE_PAIR 2
#define FOOD_PAIR 3
#define MSG_PAIR 4

#define BLANK 0
#define HEAD 1
#define BODY 2
#define FOOD 3

#define MID_Y getmaxy(stdscr) / 2
#define MID_X getmaxx(stdscr) / 2
#define START_X (MID_X - MAP_L / 2)
#define START_Y (MID_Y - MAP_H / 2)

#define DEST_X(dest) (START_X + dest % MAP_L)
#define DEST_Y(dest) (START_Y + dest / MAP_L)

struct SnakeNode{
    int dest;
    struct SnakeNode *pre, *next;
};

typedef struct SnakeNode SnakeNode;

void initMap();
void initSnake();
void drawBlock(int x, int y, short stat, short color_pair);
void generateFood();
int moveSnake(int length, int pt);
int getDirection(int pt);
void terminate(int length, int reason);
void snakeMain();

#endif //MSNAKE_SNAKE_MAIN_H_
