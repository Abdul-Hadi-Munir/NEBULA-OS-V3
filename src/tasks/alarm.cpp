#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>
#include "kernel/ipc_manager.h"

int main() {
    send_resource_request("Alarm", 15, 2);
    if (!wait_for_grant()) return 1;

    printf("\n--- NEBULA OS ALARM ---\n");
    printf("  (Press Ctrl+Z to Minimize)\n\n");

    printf("  Set alarm in how many seconds? ");
    fflush(stdout);
    char buf[16];
    if (!fgets(buf, 16, stdin)) return 1;
    int seconds = atoi(buf);

    if (seconds <= 0) {
        printf("  Error: Invalid time.\n");
    } else {
        printf("  Enter reminder message: ");
        fflush(stdout);
        char msg[128];
        if (!fgets(msg, 128, stdin)) strcpy(msg, "Wake up!");
        msg[strlen(msg)-1] = '\0';

        printf("\n  Alarm set for %d seconds from now.\n", seconds);
        time_t end_time = time(NULL) + seconds;

        while (1) {
            int remaining = end_time - time(NULL);
            if (remaining <= 0) break;

            printf("\r  Time remaining: %ds (Type 'q' to quit) ", remaining);
            fflush(stdout);

            fd_set fds;
            struct timeval tv = {1, 0};
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
                char cmd[16];
                if (fgets(cmd, 16, stdin)) {
                    if (cmd[0] == 'q' || cmd[0] == 'Q') break;
                }
            }
        }
        if (time(NULL) >= end_time) {
            printf("\n\n  ALARM!!! %s\n", msg);
        }
    }

    printf("\n  Press Enter to exit...");
    fflush(stdout);
    getchar();

    send_termination_notice(getpid());
    return 0;
}
