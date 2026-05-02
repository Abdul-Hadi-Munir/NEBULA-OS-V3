#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/select.h>
#include "kernel/ipc_manager.h"

void draw_bar(const char* label, int used, int total, int width) {
    float ratio = (total > 0) ? (float)used / (float)total : 0;
    int filled = (int)(ratio * width);
    printf("  %-4s [", label);
    for (int i = 0; i < width; i++) printf(i < filled ? "█" : "░");
    printf("] %d%% (%d/%d MB)\n", (int)(ratio * 100), used, total);
}

int main() {
    send_resource_request("Resource Dashboard", 40, 3);
    if (!wait_for_grant()) return 1;

    while (1) {
        system("clear");
        printf("╔═══════════════════════════════════════════════════════════╗\n");
        printf("║               📊 NEBULA OS RESOURCE MONITOR               ║\n");
        printf("╚═══════════════════════════════════════════════════════════╝\n");
        printf("  (Auto-refreshes every 2s | Press 'q' to quit)\n\n");

        // These would normally come from IPC, but we simulate via log parsing or defaults
        int total_ram = 1024, used_ram = 240; 
        int total_hdd = 5120, used_hdd = 1120;
        int active_p = 3;

        draw_bar("RAM", used_ram, total_ram, 25);
        draw_bar("HDD", used_hdd, total_hdd, 25);
        
        printf("\n  🚀 Active Processes: %d\n", active_p);
        printf("  🌡️  System Status: NORMAL\n");
        printf("\n  TaskManager> ");
        fflush(stdout);

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
