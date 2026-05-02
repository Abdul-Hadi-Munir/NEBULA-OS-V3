# ═══════════════════════════════════════════════════════════
# Makefile for NebulaOS — Mini Operating System Simulator
# ═══════════════════════════════════════════════════════════

CXX      = g++
CXXFLAGS = -std=c++17 -pthread -Wall -Wextra -g -Iinclude -Iinclude/kernel
LDFLAGS  = -pthread

# ─── Kernel Source Files ───
KERNEL_SRCS = src/kernel/logger.cpp \
              src/kernel/memory_manager.cpp \
              src/kernel/process_manager.cpp \
              src/kernel/scheduler.cpp \
              src/kernel/interrupt_handler.cpp \
              src/kernel/deadlock_detector.cpp \
              src/kernel/ipc_manager.cpp \
              src/kernel/storage_manager.cpp

KERNEL_OBJS = $(patsubst src/kernel/%.cpp, obj/kernel/%.o, $(KERNEL_SRCS))

# ─── Main OS Binary ───
OS_BIN = OS

# ─── Task Binaries ───
TASK_BINS = tasks/calculator \
            tasks/notepad \
            tasks/clock \
            tasks/calendar \
            tasks/create_file \
            tasks/delete_file \
            tasks/move_file \
            tasks/copy_file \
            tasks/file_info \
            tasks/rename_file \
            tasks/task_manager \
            tasks/music_player \
            tasks/minigame \
            tasks/print_file \
            tasks/instruction_guide \
            tasks/dice_roller \
            tasks/text_search \
            tasks/alarm \
            tasks/stopwatch \
            tasks/file_compression \
            tasks/log_viewer \
            tasks/mini_terminal \
            tasks/todo_list \
            tasks/resource_dashboard \
            tasks/log_daemon \
            tasks/sys_monitor

# ═══════════════════════════════════════════════════════════
# Targets
# ═══════════════════════════════════════════════════════════

.PHONY: all clean run dirs

all: dirs $(OS_BIN) $(TASK_BINS)

# Create necessary directories
dirs:
	@mkdir -p tasks
	@mkdir -p nebula_hdd
	@mkdir -p obj/kernel

# ─── Compile kernel object files ───
obj/kernel/%.o: src/kernel/%.cpp include/kernel/kernel.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ─── Link main OS binary with kernel objects ───
$(OS_BIN): src/os.cpp $(KERNEL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $< $(KERNEL_OBJS) $(LDFLAGS)

# ─── Compile each task as a standalone binary ───
tasks/%: src/tasks/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< $(LDFLAGS)

# ─── Clean all compiled files ───
clean:
	rm -f $(OS_BIN) $(TASK_BINS)
	rm -rf obj/kernel/*.o
	rm -f system.log

# ─── Run the OS with default parameters ───
run: all
	./OS
