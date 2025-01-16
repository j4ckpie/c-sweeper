#include <stdio.h>
#include <unistd.h>

#include "game_controller.h"

int main(int argc, char **argv) {
    int opt;
    char *file_path = NULL;

    while((opt = getopt(argc, argv, "f:")) != -1) {
        switch(opt) {
            case 'f':
                file_path = optarg;
                break;
        }
    }

    game(file_path);
    
    return 0;
}