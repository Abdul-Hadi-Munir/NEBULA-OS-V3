#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "kernel/ipc_manager.h"

int main() {
    send_resource_request("Minigame", 35, 3);
    if (!wait_for_grant()) return 1;

    srand(time(NULL) ^ getpid());

    printf("\n--- NEBULA OS MINIGAME ---\n");
    printf("  (Press Ctrl+Z to Minimize)\n\n");

    int playing = 1;
    while (playing) {
        int secret = (rand() % 100) + 1;
        int guesses = 7;
        int won = 0;

        printf("  I'm thinking of a number (1-100).\n");
        printf("  You have %d guesses.\n\n", guesses);

        for (int i = 1; i <= guesses; i++) {
            printf("  Guess #%d: ", i);
            fflush(stdout);
            char buf[16];
            if (!fgets(buf, 16, stdin)) break;
            int g = atoi(buf);

            if (g == secret) {
                printf("  Correct! You won!\n");
                won = 1;
                break;
            } else if (g < secret) {
                printf("  Too low!\n");
            } else {
                printf("  Too high!\n");
            }
        }

        if (!won) printf("  Game over. The number was %d.\n", secret);

        printf("\n  Play again? (y/n): ");
        fflush(stdout);
        char buf[16];
        if (!fgets(buf, 16, stdin) || (buf[0] != 'y' && buf[0] != 'Y')) playing = 0;
    }

    printf("\n  Thanks for playing!\n");
    send_termination_notice(getpid());
    return 0;
}
