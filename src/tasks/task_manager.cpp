#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include "kernel/ipc_manager.h"

#define MAX_LOG_DISPLAY 20
#define LINE_SIZE 256

void display_process_table() {
    printf("\n--- TASK MANAGER ---\n");
    FILE* f = fopen("system.log", "r");
    if (!f) {
        printf("  Cannot read system.log\n");
        return;
    }

    char lines[100][LINE_SIZE];
    int count = 0;
    char buf[LINE_SIZE];
    while (fgets(buf, LINE_SIZE, f)) {
        if (strstr(buf, "Process") || strstr(buf, "Resources") || strstr(buf, "Context")) {
            strncpy(lines[count % 100], buf, LINE_SIZE - 1);
            count++;
        }
    }
    fclose(f);

    printf("  Last %d system events:\n", MAX_LOG_DISPLAY);
    int start = (count > MAX_LOG_DISPLAY) ? (count - MAX_LOG_DISPLAY) : 0;
    for (int i = start; i < count; i++) {
        printf("  %s", lines[i % 100]);
    }
}

int main() {
    send_resource_request("Task Manager", 50, 5);
    if (!wait_for_grant()) return 1;

    while (1) {
        display_process_table();
        printf("\n  [K] Kill  [P] Priority  [Q] Quit\n  Command: ");
        fflush(stdout);

        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        struct timeval tv = {2, 0};

        int ret = select(STDIN_FILENO + 1, &fds, 0, 0, &tv);
        if (ret > 0) {
            char cmd[64];
            if (!fgets(cmd, 64, stdin)) break;
            char c = cmd[0];
            if (c == 'q' || c == 'Q') break;
            else if (c == 'k' || c == 'K') {
                printf("  Enter PID to kill: ");
                char pid_buf[16];
                fgets(pid_buf, 16, stdin);
                kill(atoi(pid_buf), SIGTERM);
            }
            else if (c == 'p' || c == 'P') {
                printf("  Enter PID: ");
                char pid_buf[16]; fgets(pid_buf, 16, stdin);
                printf("  Enter new priority (0-10): ");
                char pri_buf[16]; fgets(pri_buf, 16, stdin);

                printf("  Priority change request sent (simulated).\n");
                sleep(1);
            }
        }
    }

    send_termination_notice(getpid());
    return 0;
}
