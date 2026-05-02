#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include "kernel/ipc_manager.h"

#define MAX_LINES 100
#define LINE_SIZE 128

static char text_buffer[MAX_LINES][LINE_SIZE];
static int line_count = 0;
static pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
static int notepad_running = 1;
static char current_filename[64];

void generate_filename() {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    strftime(current_filename, 64, "note_%Y%m%d_%H%M%S.txt", t);
}

void save_to_file() {
    char path[128];
    sprintf(path, "nebula_hdd/%s", current_filename);
    pthread_mutex_lock(&buffer_lock);
    FILE* f = fopen(path, "w");
    if (f) {
        for (int i = 0; i < line_count; i++) {
            fprintf(f, "%s\n", text_buffer[i]);
        }
        fclose(f);
        printf("\n  [Saved to %s]\n", path);
    }
    pthread_mutex_unlock(&buffer_lock);
}

void* autosave_thread(void* arg) {
    (void)arg;
    while (notepad_running) {
        for (int i = 0; i < 10 && notepad_running; i++) sleep(1);
        if (line_count > 0 && notepad_running) save_to_file();
    }
    return NULL;
}

int main() {
    send_resource_request("Notepad", 40, 10);
    if (!wait_for_grant()) return 1;

    generate_filename();

    printf("\n--- NEBULA OS NOTEPAD ---\n");
    printf("  (Press Ctrl+Z to Minimize)\n\n");
    printf("  File: %s\n", current_filename);
    printf("  Commands: :save, :quit\n\n");

    pthread_t autosave_tid;
    pthread_create(&autosave_tid, NULL, autosave_thread, NULL);

    char line[LINE_SIZE];
    while (notepad_running) {
        printf("  %d| ", line_count + 1);
        fflush(stdout);
        if (!fgets(line, LINE_SIZE, stdin)) break;
        line[strlen(line)-1] = '\0';

        if (strcmp(line, ":quit") == 0) {
            save_to_file();
            notepad_running = 0;
            break;
        }
        if (strcmp(line, ":save") == 0) {
            save_to_file();
            continue;
        }

        pthread_mutex_lock(&buffer_lock);
        if (line_count < MAX_LINES) {
            strncpy(text_buffer[line_count], line, LINE_SIZE-1);
            line_count++;
        }
        pthread_mutex_unlock(&buffer_lock);
    }

    notepad_running = 0;
    pthread_join(autosave_tid, NULL);

    send_termination_notice(getpid());
    return 0;
}
