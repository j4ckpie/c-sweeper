#include <stdio.h>

#include "io.h"

int main(void) {
    save_scoreboard("scoreboard.txt", "szef", 999);
    print_scoreboard("scoreboard.txt");
    return 0;
}