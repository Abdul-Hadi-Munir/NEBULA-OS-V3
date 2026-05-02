#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include "kernel/ipc_manager.h"

void draw_bar(const char* label, int used, int total, int width) {
    float ratio = (total > 0) ? (float)used / (float)total : 0;
    int filled = (int)(ratio * width);
    printf("  %s [", label);
    for (int i = 0; i < width; i++) printf(i < filled ? "#" : ".");
    printf("] %d%% (%d/%d)\n", (int)(ratio * 100), used, total);
}

int main() {
    send_resource_request("Resource Dashboard", 40, 3);
    if (!wait_for_grant()) return 1;

    while (1) {
        printf("\n--- NEBULA OS RESOURCE DASHBOARD ---\n");
        printf("  (Press Ctrl+Z to Minimize)\n\n");

        int total_ram = 2048, free_ram = 2048;
        int total_hdd = 262144, free_hdd = 262144;
        int active_p = 0;

        FILE* f = fopen("system.log", "r");
        if (f) {
            char buf[256];
            while (fgets(buf, 256, f)) {
                if (strstr(buf, "Free RAM=")) {
                    char* p = strstr(buf, "Free RAM=");
                    free_ram = atoi(p + 9);
                }
                if (strstr(buf, "Free HDD=")) {
                    char* p = strstr(buf, "Free HDD=");
                    free_hdd = atoi(p + 9);
                }
                if (strstr(buf, "Process created")) active_p++;
                if (strstr(buf, "Process terminated")) active_p--;
            }
            fclose(f);
        }
        if (active_p < 0) active_p = 0;

        draw_bar("RAM", total_ram - free_ram, total_ram, 20);
        draw_bar("HDD", total_hdd - free_hdd, total_hdd, 20);
        printf("\n  Active Processes: %d\n", active_p);
        printf("\n  [Q]uit (Refreshes every 2s)\n");

        fd_set fds;
        struct timeval tv = {2, 0};
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
            char cmd[16];
            if (fgets(cmd, 16, stdin) && (cmd[0] == 'q' || cmd[0] == 'Q')) break;
        }
    }

    send_termination_notice(getpid());
    return 0;
}
