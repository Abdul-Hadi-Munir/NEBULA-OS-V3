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
    *   `SIGTSTP`: Minimizes a task to the background (triggered via Ctrl+Z).
    *   `SIGCONT`: Resumes a task to the foreground.
    *   `SIGTERM`: Graceful termination.

---

## 🚀 Deployment & Installation Guide

Follow these steps to deploy NebulaOS V3 on your local Linux environment:

### 1. Environment Preparation
Ensure your system has the necessary build tools and libraries installed:
```bash
# Update your package manager
sudo apt update

# Install build-essential (includes g++ and make)
sudo apt install build-essential

# Install mpg123 (required for the Music Player)
sudo apt install mpg123
```

### 2. Cloning & Compilation
Clone the repository and build the binaries using the provided Makefile:
```bash
# Clone the repository
git clone https://github.com/Abdul-Hadi-Munir/NEBULA-OS-V3.git
cd NEBULA-OS-V3

# Clean previous builds and compile
make clean
make
```

### 3. Initial Configuration
When you launch the OS for the first time (`./OS`), you will enter the **Configuration Phase**:
*   **RAM (GB):** Total physical memory you want to simulate (e.g., `4`).
*   **HDD (GB):** Virtual storage capacity (e.g., `100`).
*   **Cores:** Number of CPU cores for the scheduler (e.g., `4`).

---

## 🖥️ Operating Workflow

### Launching the Kernel
```bash
./OS
```

### Navigating the Dashboard
Once the boot sequence is complete, you will see the **Nebula Dashboard**:
*   **Running a Task:** Simply enter the task number (1-23). The screen will clear, and the task will take the foreground.
*   **Multitasking (Minimize):** While in a task, press **Ctrl+Z**. The kernel will catch the signal, suspend the task, and return you to the dashboard.
*   **Managing Background Tasks:** 
    *   Press **[M]** to view all background/minimized tasks.
    *   Press **[F]** and enter a PID to bring a specific task back to the foreground.
*   **System Logs:** Press **[L]** to view real-time kernel logs. Press **[C]** inside the log viewer to clear the history.

---

## 📁 Detailed Task Suite

### 📄 Professional Notepad
*   **Features:** Vim-style commands, internal 500-line buffer, and thread-safe autosave.
*   **Usage:** Type `:w` to save, `:q` to quit, and `:help` for a list of commands.

### 🎵 Advanced Music Player
*   **Features:** Real MP3 playback via `mpg123`.
*   **Usage:** Scans the `music/` folder automatically. Select a song by number.

### ⏰ Alarm & Background Daemons
*   **Features:** Double-forked background execution.
*   **Usage:** Set an alarm and choose "Run in background". The OS will beep and notify you even after you exit the app.

---

## 🛠️ Troubleshooting
*   **Permission Denied:** Ensure you have write permissions for `/tmp/` and the project directory.
*   **Audio Issues:** Verify `mpg123` is installed. Run `which mpg123` to check the path.
*   **Build Errors:** Ensure you are using `g++` with C++17 support (`g++ --version` should be 7.0 or higher).

---

*NebulaOS V3: Engineering Minimalism.*




