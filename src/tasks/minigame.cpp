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
    system("clear");

    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                   NEBULA OS NUMBER GUESSER                ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");
    printf("  (Press 'q' at any time to quit | Press Ctrl+Z to minimize)\n\n");

    int playing = 1;
    while (playing) {
        int secret = (rand() % 100) + 1;
        int guesses = 7;
        int won = 0;

        printf("  [ New Game ] I'm thinking of a number between 1 and 100.\n");
        printf("  You have %d attempts. Good luck!\n\n", guesses);

        for (int i = 1; i <= guesses; i++) {
            printf("  Attempt #%d - Enter your guess: ", i);
            fflush(stdout);
            
            char buf[16];
            if (!fgets(buf, 16, stdin)) { playing = 0; break; }
            
            if (buf[0] == 'q' || buf[0] == 'Q') {
                playing = 0;
                break;
            }

            int g = atoi(buf);
            if (g <= 0) {
                printf("  [!] Please enter a valid number.\n");
                i--; continue;
            }

            if (g == secret) {
                printf("\n  ✨ CORRECT! The number was %d. You won in %d tries! ✨\n", secret, i);
                won = 1;
                break;
            } else if (g < secret) {
                printf("  [↑] Too low!\n");
            } else {
                printf("  [↓] Too high!\n");
            }
        }

        if (!playing) break;
        if (!won) printf("\n  [✘] Game over. The secret number was %d.\n", secret);

        printf("\n  Play again? (y/n): ");
        fflush(stdout);
        char buf[16];
        if (!fgets(buf, 16, stdin) || (buf[0] != 'y' && buf[0] != 'Y')) playing = 0;
        if (playing) system("clear");
    }

    printf("\n  Thanks for playing Nebula Guess! Goodbye.\n");
    send_termination_notice(getpid());
    return 0;
}
