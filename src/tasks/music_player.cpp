#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>
#include "kernel/ipc_manager.h"

int main() {
    send_resource_request("Music Player", 20, 5);
    if (!wait_for_grant()) return 1;

    printf("\n--- NEBULA OS MUSIC PLAYER ---\n");
    printf("  (Press Ctrl+Z to Minimize)\n\n");
    printf("  ♪ Now Playing: NebulaOS Theme...\n\n");

    int duration = 30;
    time_t end_time = time(NULL) + duration;

    while (1) {
        time_t now = time(NULL);
        int remaining = end_time - now;
        if (remaining < 0) break;
        int elapsed = duration - remaining;

        int filled = (elapsed * 20) / duration;
        printf("\r  Playing... [");
        for (int i = 0; i < 20; i++) printf(i < filled ? "#" : ".");
        printf("] %d%% ", (elapsed * 100) / duration);
        fflush(stdout);

        fd_set fds;
        struct timeval tv = {1, 0};
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
            char buf[16];
            if (fgets(buf, 16, stdin)) {
                if (buf[0] == 'q' || buf[0] == 'Q') break;
            }
        }
    }

    printf("\n\n  ♪ Song complete!\n");
    printf("\n  Press Enter to exit...");
    fflush(stdout);
    getchar();

    send_termination_notice(getpid());
    return 0;
}
