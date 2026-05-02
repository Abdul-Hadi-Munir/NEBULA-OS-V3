# NEBULA OS V3 🚀
**A Comprehensive Minimalist Operating System Simulation**

NebulaOS V3 is a high-fidelity operating system simulator implemented in C++17. It explores advanced systems programming concepts such as multi-level feedback queues, resource allocation protocols, inter-process communication, and process lifecycle management within a strictly minimalist CLI architecture.

---

## 🏛️ Kernel Architecture Deep-Dive

### 1. Multi-Level Queue (MLQ) Scheduler
NebulaOS utilizes a tiered scheduling strategy to handle diverse workload profiles:
*   **Queue 0 (High Priority):** Reserved for system-critical tasks and real-time alerts. It uses a preemptive priority-based approach.
*   **Queue 1 (Round Robin):** Dedicated to interactive user applications (e.g., Notepad, Calculator). It uses a defined time-quantum to ensure responsive multitasking.
*   **Queue 2 (FCFS):** Handles batch or background tasks where execution order is more critical than response time.

### 2. Process Management & PCB
Every task in NebulaOS is managed via a **Process Control Block (PCB)** which tracks:
*   **PID:** Unique Process Identifier.
*   **State:** (RUNNING, WAITING, STOPPED, TERMINATED).
*   **Priority:** Dynamic priority level (0-10).
*   **Resource Map:** Tracking RAM, HDD, and CPU cores allocated to the process.

### 3. IPC & Signal Handling
NebulaOS implements a custom **IPC Manager** using **POSIX Named Pipes (FIFOs)**:
*   **Communication Protocol:** Tasks send resource requests and termination notices via `/tmp/nebula_pipe_[PID]`.
*   **Kernel Signals:** Uses Unix signals for process control:
    *   `SIGTSTP`: Minimizes a task to the background.
    *   `SIGCONT`: Resumes a task to the foreground.
    *   `SIGTERM`: Graceful termination.

### 4. Resource & Memory Management
The kernel maintains a global resource registry protected by **pthreads mutexes**:
*   **Memory Bank:** Tracks fragmented memory blocks (simulated).
*   **HDD Registry:** Manages virtual storage in the `nebula_hdd/` directory.
*   **Core Allocation:** Prevents CPU over-subscription by blocking task launches if no cores are available.

---

## 📁 Detailed Task Suite

### 📄 Professional Notepad
A production-grade text editor within the CLI.
*   **Vim-Style Commands:** `:w` (save), `:q` (quit), `:wq` (save & exit).
*   **Internal Buffering:** Supports up to 500 lines of text with thread-safe autosave.
*   **Interface:** Clean line-numbering and status bar.

### 🎵 Advanced Music Player
A real-time audio playback utility.
*   **Backend:** Powered by `mpg123`.
*   **Library:** Dynamic scanning of the `music/` directory for `.mp3` files.
*   **Control:** Interactive menu for song selection and 'q' to stop playback.

### ⏰ Alarm & Background Daemons
Demonstrates true OS background services.
*   **Daemonization:** Uses double-forking to keep the alarm alive after the UI exits.
*   **Notifications:** Triggers system beeps (`\a`) and logs events to the kernel.

### 📊 System Utilities
*   **Task Manager:** Real-time process monitoring with 'Kill' and 'Priority' controls.
*   **Resource Monitor:** Accurate visualization of RAM/HDD usage via block-character graphs.
*   **Log Viewer:** Live feed of kernel events with 'Clear' functionality.

---

## 🛠️ Technical Implementation
*   **Concurrency:** Heavy use of `pthreads` for asynchronous IPC handling and background monitoring.
*   **Synchronization:** Mutexes and Condition Variables (`pthread_cond_t`) ensure zero race conditions in the kernel.
*   **Terminal Control:** `termios.h` is used to implement "Raw Mode" for instant keypress detection in the Clock and Games.

---

## 🚀 Execution & Deployment

### Build Instructions
```bash
make clean && make
```

### Resource Configuration
Upon launch (`./OS`), the user must specify:
1.  **RAM:** Total system memory in GB.
2.  **HDD:** Total virtual storage in GB.
3.  **Cores:** Number of available CPU cores for multitasking.

---

**Developed by Abdul Hadi Munir**  
*NebulaOS V3: Engineering Minimalism.*
