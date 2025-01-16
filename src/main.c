#include <stdio.h>
#include <unistd.h>

#include "game_controller.h"

int main(int argc, char **argv) {
    int opt;
    char *file_path = NULL;

    // Get and handle command-line arguments
    while((opt = getopt(argc, argv, "f:")) != -1) {
        switch(opt) {
            case 'f':
                file_path = optarg;
                break;
        }
    }

    // Start game
    game(file_path);
    
    return 0;
}