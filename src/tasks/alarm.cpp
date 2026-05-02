#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/select.h>
#include <fcntl.h>
#include "kernel/ipc_manager.h"

void play_alarm_sound() {
    // Attempt to beep and play a sound
    for (int i = 0; i < 5; i++) {
        printf("\a"); // System beep
        fflush(stdout);
        system("mpg123 -q music/cosmic_vibes.mp3 --frames 100 > /dev/null 2>&1");
        sleep(1);
    }
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
        msg[strlen(msg)-1] = '\0';

        printf("\n  🔔 Alarm set for %d seconds from now.\n", seconds);
        printf("  [1] Keep open (Foreground)\n");
        printf("  [2] Run in background & Exit UI\n");
        printf("  Choice: ");
        fflush(stdout);
        
        char choice_buf[16];
        fgets(choice_buf, 16, stdin);
        
        if (choice_buf[0] == '2') {
            printf("\n  [✔] Alarm daemonized! It will beep when time is up.\n");
            printf("  You can now use other OS features.\n");
            sleep(1);
            
            pid_t pid = fork();
            if (pid == 0) {
                // Background Daemon
                setsid();
                int devnull = open("/dev/null", O_WRONLY);
                dup2(devnull, 0); // Still want to see beeps on main terminal if possible?
                // Actually daemon shouldn't have terminal. 
                // But we want it to beep.
                sleep(seconds);
                play_alarm_sound();
                _exit(0);
            }
            // Parent exits UI
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
        
        printf("\n\n  🚨 ALARM!!! 🚨\n  Message: %s\n", msg);
        play_alarm_sound();
    }

    printf("\n  Press Enter to exit...");
    fflush(stdout);
    getchar();

    send_termination_notice(getpid());
    return 0;
}
