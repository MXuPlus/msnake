#include "snake_main.h"

short *Map;
SnakeNode *SnakeHT[2];
char stat_ch[5] = {' ', '@', 'O', '$'};

// In this function, we configure the map
void initMap() {
    Map = (short *) calloc(MAP_H * MAP_L, (sizeof(short)));
    generateFood();
}

// Generate the snake head, this is the first snake body part
void initSnake() {
    SnakeNode* head = (SnakeNode*) malloc(sizeof(SnakeNode));
    head->dest = (MAP_H/2-1)*MAP_L+MAP_L/2;
    SnakeHT[0] = SnakeHT[1] = head;
    drawBlock(DEST_X(head->dest), DEST_Y(head->dest), HEAD, SNAKE_PAIR);
}

// Draw blocks on screen
void drawBlock(int x, int y, short stat, short color_pair) {
    attron(COLOR_PAIR(color_pair));
    attron(A_BOLD);
    mvaddch(y, x, stat_ch[stat]);
    attroff(COLOR_PAIR(color_pair));
    attroff(A_BOLD);
    refresh();
}

void generateFood() {
    int fdest;
    srand(time(NULL));
    // Use this loop to avoid generating the food on non-blank block
    do {
        fdest = rand() % (MAP_H*MAP_L);
    } while (Map[fdest]!=BLANK);
    Map[fdest] = FOOD;
    drawBlock(DEST_X(fdest), DEST_Y(fdest), FOOD, FOOD_PAIR);
}

// In this function, we will move the snake
int moveSnake(int length, int d) {
    int nhdest = SnakeHT[0]->dest+d;
    int nx = nhdest % MAP_L, px = SnakeHT[0]->dest % MAP_L;
    if (nhdest >= MAP_L*MAP_H || nhdest < 0 || abs(px-nx)>1) {
        return -1; // -1 means your snake hit the wall
    } else {
        if (Map[nhdest]==BODY) return -2; // -2 means your snake hit your body
        SnakeNode *nhead = (SnakeNode*) malloc(sizeof(SnakeNode)),*phead = SnakeHT[0], *ptail = SnakeHT[1];
        nhead->dest = nhdest;
        int phstat = Map[nhdest], phdest = phead->dest, ptdest = ptail->dest;

        Map[nhdest]=HEAD; // Update the head in Map
        nhead->pre = NULL; nhead->next = phead;
        phead->pre = nhead;
        ptail->pre->next = NULL;
        // Update SNAKE_HEAD_TAIL table
        SnakeHT[0] = nhead; SnakeHT[1] = ptail->pre;
        // Update Map
        Map[phdest] = BODY; Map[ptdest]=BLANK;
        free(ptail); // Release memory used by previous tail
        if (phstat==FOOD) {
            SnakeNode *ntail = (SnakeNode *) malloc(sizeof(SnakeNode));
            ntail->next = NULL; ntail->pre = SnakeHT[1]; ntail->dest = ptdest;
            // We release the tail node...
            SnakeHT[1]->next = ntail;
            SnakeHT[1] = ntail;
            Map[ptdest]=BODY;
            length++;
            generateFood();
        }
        // Update screen
        drawBlock(DEST_X(nhdest), DEST_Y(nhdest), Map[nhdest], SNAKE_PAIR);
        drawBlock(DEST_X(phdest), DEST_Y(phdest), Map[phdest], SNAKE_PAIR);
        drawBlock(DEST_X(ptdest), DEST_Y(ptdest), Map[ptdest], SNAKE_PAIR);
    }
    return length;
}

int getDirection(int pt) {
    int d[4] = {MAP_L, -MAP_L, -1, 1};
    int c=getch(), tmp=((c>=0402&&c<=0405)?d[c-0402]:pt);
    return (tmp+pt == 0)?pt:tmp;
}

void terminate(int length, int reason) {
    SnakeNode *head = SnakeHT[0], *p;
    while (head) {
        p = head->next;
        free(head);
        head = p;
    }
    free(Map);
    attron(COLOR_PAIR(MSG_PAIR));
    attron(A_BOLD);
    char err_msg1[] = "YOU LOST FOR HITTING THE WALL!";
    char err_msg2[] = "YOU LOST FOR HITTING YOURSELF!";
    char *msg = reason==-1? err_msg1 : err_msg2;
    mvprintw(MID_Y-1, MID_X-13, "%s", msg);
    mvprintw(MID_Y, MID_X-7, "YOUR SCORE: %d", length*10);
    attroff(COLOR_PAIR(MSG_PAIR));
    attroff(A_BOLD);
    storeData(length*10);
    refresh();
}

void snakeMain() {
    // Init the map and init the snake
    initMap();
    initSnake();
    halfdelay(10/FPS);
    curs_set(0);
    int d = 1, length = 1, tmp = 1;
    while (length>0) {
        d = getDirection(d);
        length = moveSnake(length, d);
        tmp = length <= 0 ? tmp : length;
    }
    terminate(tmp, length);
    nocbreak();
    confScreen();
    getch();
    repaintScreen();
}

