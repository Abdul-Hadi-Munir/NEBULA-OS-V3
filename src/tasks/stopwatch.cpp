#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/select.h>
#include "kernel/ipc_manager.h"

int main() {
    send_resource_request("Stopwatch", 15, 1);
    if (!wait_for_grant()) return 1;

    printf("\n--- NEBULA OS STOPWATCH ---\n");
    printf("  (Press Ctrl+Z to Minimize)\n\n");

    printf("  [1] Stopwatch\n  [2] Countdown\n  Choice: ");
    fflush(stdout);
    char choice[16];
    if (!fgets(choice, 16, stdin)) return 1;

    if (choice[0] == '2') {
        printf("  Enter seconds: ");
        fflush(stdout);
        char buf[16];
        fgets(buf, 16, stdin);
        int total = atoi(buf);
        time_t end = time(NULL) + total;
        while (1) {
            int rem = end - time(NULL);
            if (rem <= 0) break;
            printf("\r  Remaining: %02d:%02d  ", rem/60, rem%60);
            fflush(stdout);
            sleep(1);
        }
        printf("\r  Time's up!      \n");
    } else {
        printf("  Stopwatch started. [Enter]=Lap, [S]=Stop\n");
        time_t start = time(NULL);
        int laps = 0;
        while (1) {
            int elapsed = time(NULL) - start;
            printf("\r  Elapsed: %02d:%02d  ", elapsed/60, elapsed%60);
            fflush(stdout);

            fd_set fds;
            struct timeval tv = {1, 0};
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            if (select(STDIN_FILENO+1, &fds, NULL, NULL, &tv) > 0) {
                char buf[16];
                if (fgets(buf, 16, stdin)) {
                    if (buf[0] == 's' || buf[0] == 'S') break;
                    printf("\n  Lap %d: %02d:%02d\n", ++laps, elapsed/60, elapsed%60);
                }
            }
        }
    }

    printf("\n  Press Enter to exit...");
    fflush(stdout);
    getchar();

    send_termination_notice(getpid());
    return 0;
}
