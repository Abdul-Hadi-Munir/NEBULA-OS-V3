#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <fcntl.h>
#include "kernel/ipc_manager.h"

void trigger_alarm(const char* msg) {
    // Strictly 3 beeps
    for (int i = 0; i < 3; i++) {
        printf("\a"); // System beep
        fflush(stdout);
        system("echo -ne '\007' > /dev/tty 2>/dev/null"); 
        usleep(500000); // 0.5s pause between beeps
    }
    
    printf("\n\n  🔔  [NEBULA OS REMINDER]  🔔\n");
    printf("  MESSAGE: %s\n\n", msg);
    fflush(stdout);
}

int main() {
    send_resource_request("Alarm", 15, 2);
    if (!wait_for_grant()) return 1;

    system("clear");
    printf("╔═══════════════════════════════════════════════════════════╗\n");
    printf("║                   NEBULA OS ALARM & REMINDER              ║\n");
    printf("╚═══════════════════════════════════════════════════════════╝\n");

    printf("  ⏰ Set alarm in (seconds): ");
    fflush(stdout);
    char buf[16];
    if (!fgets(buf, 16, stdin)) return 1;
    int seconds = atoi(buf);

    if (seconds <= 0) {
        printf("  [!] Invalid time duration.\n");
    } else {
        printf("  📝 Reminder message: ");
        fflush(stdout);
        char msg[128];
        if (!fgets(msg, 128, stdin)) strcpy(msg, "Wake up!");
        msg[strcspn(msg, "\n")] = 0; 

        printf("\n  🔔 Alarm set for %d seconds from now.\n", seconds);
        printf("  [1] Keep open (Foreground)\n");
        printf("  [2] Run in background & Exit UI\n");
        printf("  Choice: ");
        fflush(stdout);
        
        char choice_buf[16];
        fgets(choice_buf, 16, stdin);
        
        if (choice_buf[0] == '2') {
            printf("\n  [✔] Alarm daemonized! It will beep 3 times when ready.\n");
            sleep(1);
            
            pid_t pid = fork();
            if (pid == 0) {
                // Background Daemon
                setsid();
                sleep(seconds);
                
                // Open terminal for output
                int tty = open("/dev/tty", O_WRONLY);
                if (tty >= 0) {
                    dprintf(tty, "\a\a\a\n\n  🔔  [NEBULA OS REMINDER]  🔔\n");
                    dprintf(tty, "  MESSAGE: %s\n\n", msg);
                    close(tty);
                }
                
                // Strictly 3 beeps to /dev/tty
                system("echo -ne '\007\007\007' > /dev/tty 2>/dev/null");
                
                _exit(0);
            }
            send_termination_notice(getpid());
            return 0;
        }

        // Foreground monitoring
        time_t end_time = time(NULL) + seconds;
        while (1) {
            int remaining = end_time - time(NULL);
            if (remaining <= 0) break;

            printf("\r  ⏳ Time remaining: %ds | Press 'q' to cancel: ", remaining);
            fflush(stdout);

            fd_set fds;
            struct timeval tv = {1, 0};
            FD_ZERO(&fds);
            FD_SET(STDIN_FILENO, &fds);
            if (select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0) {
                char cmd[16];
                if (fgets(cmd, 16, stdin)) {
                    if (cmd[0] == 'q' || cmd[0] == 'Q') {
                        printf("\n  [✘] Alarm cancelled.\n");
                        send_termination_notice(getpid());
                        return 0;
                    }
                }
            }
        }
        
        trigger_alarm(msg);
    }

    printf("\n  Press Enter to exit...");
    fflush(stdout);
    getchar();

    send_termination_notice(getpid());
    return 0;
}
