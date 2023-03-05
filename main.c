#include "msnake.h"

// todo: More beutiful UI

int main() {
    dbInit();
    initGame();
    int option;
    while ((option = showMenu()) != 3) {
        repaintScreen();
        if (option == 1) snakeMain();
        else if (option == 2) showHistory();
    }
    endwin();
    dbClose();
    return 0;
}