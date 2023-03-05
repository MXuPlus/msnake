#ifndef MSNAKE_SNAKE_DATA_H_
#define MSNAKE_SNAKE_DATA_H_

#include "msnake.h"

#define DBFILE "msnake.dat"

struct ScoreData {
    char game_time[21];
    int score;
};

void dbInit();
void storeData(int score);
struct ScoreData *getData();
void dbClose();

#endif //MSNAKE_SNAKE_DATA_H_
