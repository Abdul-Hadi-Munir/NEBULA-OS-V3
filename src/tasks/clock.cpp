#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include "kernel/ipc_manager.h"

static int clock_running = 1;

void handle_signal(int sig) {
    (void)sig;
    clock_running = 0;
}

int main() {
    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    send_resource_request("Clock", 10, 1);
    if (!wait_for_grant()) return 1;

    printf("\n--- NEBULA OS SYSTEM CLOCK ---\n");
    printf("  (Press Ctrl+Z to Minimize)\n\n");

    while (clock_running) {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        char time_str[64];
        strftime(time_str, 64, "%H:%M:%S | %A, %B %d, %Y", t);

        printf("\r  %s    ", time_str);
        fflush(stdout);
        sleep(1);
    }

    send_termination_notice(getpid());
    return 0;
}
