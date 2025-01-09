#include <stdio.h>

#include "io.h"

int main(void) {
    save_current_score("all_scores.txt", "szef", 999);
    print_scoreboard("scoreboard.txt");
    return 0;
}