#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "kernel/ipc_manager.h"

void draw_die(int value) {
    printf("  [ %d ]\n", value);
}

int main() {
    send_resource_request("Dice Roller", 20, 1);
    if (!wait_for_grant()) return 1;

    srand(time(NULL) ^ getpid());

    printf("\n--- NEBULA OS DICE ROLLER ---\n");
    printf("  (Press Ctrl+Z to Minimize)\n\n");

    while (1) {
        printf("  How many dice? (1-6, 0 to quit): ");
        fflush(stdout);
        char buf[16];
        if (!fgets(buf, 16, stdin)) break;
        int count = atoi(buf);
        if (count == 0) break;
        if (count < 0 || count > 6) {
            printf("  Invalid number of dice.\n");
            continue;
        }

        printf("  Rolling %d dice...\n", count);
        int total = 0;
        for (int i = 0; i < count; i++) {
            int roll = (rand() % 6) + 1;
            draw_die(roll);
            total += roll;
        }
        printf("  Total: %d\n\n", total);
    }

    send_termination_notice(getpid());
    return 0;
}
