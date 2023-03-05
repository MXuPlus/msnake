#include <string.h>
#include "snake_data.h"

FILE *db;

void dbInit() {
    db = fopen(DBFILE, "a+");
    if (db == NULL) {
        printf("Error: Database file error.\n");
        exit(3);
    }
}

void storeData(int score) {
    time_t raw_time;
    struct tm *time_info;

    char time_str[21];
    time(&raw_time);
    time_info = localtime(&raw_time);
    strftime(time_str, 21, "%Y-%m-%d--%H:%M:%S", time_info);

    fprintf(db, "%s %8d\n", time_str, score);
}

struct ScoreData *getData() {
    fseek(db, 0, SEEK_END);
    struct ScoreData *list = (struct ScoreData*) calloc(10, sizeof(struct ScoreData));
    long dblen = ftell(db), offset = dblen - 10 * 30;
    if (offset < 0) offset = 0;

    fseek(db, offset, SEEK_SET);
    for (int i = 0; i < 10; ++i) {
        fscanf(db, "%s %d", list[i].game_time, &list[i].score);
    }
    return list;
}

void dbClose() {
    fclose(db);
}