#include "player.h"

// Compare function for quick sort algorithm
int comp(const void *a, const void *b) {
    Player *an = (Player *)a;
    Player *bn = (Player *)b;
    return bn->score - an->score;
}