# NEBULA OS V3 🚀
**A Comprehensive Professional Operating System Simulation**

NebulaOS V3 is a high-fidelity operating system simulator implemented in C++17. It explores advanced systems programming concepts such as multi-level feedback queues, resource allocation protocols, inter-process communication, and process lifecycle management within a strictly minimalist CLI architecture.

---

## 📖 Table of Contents
1. [System Architecture](#-system-architecture)
2. [Kernel Components](#-kernel-components)
3. [The Professional Task Suite](#-the-professional-task-suite)
4. [Deployment Guide](#-deployment-guide)
5. [Usage Instructions](#-usage-instructions)
6. [Troubleshooting & FAQ](#-troubleshooting--faq)

---

## 🏛️ System Architecture

NebulaOS operates on a **Micro-Kernel Inspired** architecture where the core OS handles scheduling and resource management, while all applications (tasks) run in isolated user-space processes.

### Kernel Layers:
*   **Hardware Abstraction (Simulated):** Manages virtual RAM and HDD resources.
*   **Process Management:** Tracks every task via a **Process Control Block (PCB)**.
*   **Scheduler:** A three-tier **Multi-Level Queue (MLQ)** system.
*   **IPC Bridge:** Uses **Named Pipes** for bidirectional communication between the Kernel and Tasks.

---

## 🧠 Kernel Components

### 1. The MLQ Scheduler
The scheduler manages tasks based on their behavior and priority:
*   **Queue 0 (Priority):** For real-time tasks. If a task is in Q0, it is executed immediately.
*   **Queue 1 (Round Robin):** For interactive apps. Each task gets a "Time Slice". If it doesn't finish, it moves to the back of the line.
*   **Queue 2 (FCFS):** For background batch tasks. First come, first served.

### 2. Resource Guard
NebulaOS prevents "System Crashes" by strictly enforcing resource limits:
*   When you launch a task, it sends a **Resource Request** (e.g., "I need 64MB RAM").
*   The Kernel checks if `free_RAM >= request`. If not, the task waits in the **Ready Queue**.
*   This ensures the OS never "runs out" of memory unexpectedly.

---

## 📁 The Professional Task Suite

### 📄 Notepad (Pro Editor)
*   **How to use:** Type your text normally.
*   **Commands:**
    *   `:w` - Saves the file to `nebula_hdd/`.
    *   `:q` - Quits the editor (auto-saves).
    *   `:wq` - Save and Quit.
    *   `:help` - View all commands.

### 🎵 Music Player (MP3 Support)
*   **How to use:** Select a song number from the generated list.
*   **Tech:** Uses `mpg123` for high-quality audio.
*   **Control:** Press `q` while a song is playing to stop it and return to the menu.

### ⏰ Alarm & Daemon
*   **Backgrounding:** You can set an alarm and choose "Run in background". This forks a **Daemon Process** that stays alive even if you exit the Alarm app!
*   **Notification:** It will beep (`\a`) and play a sound when the timer expires.

---

## 🚀 Deployment Guide

Follow these steps to deploy NebulaOS V3 on your local machine:

### 1. Environment Setup
Ensure you have the necessary tools installed:
```bash
# Ubuntu/Debian
sudo apt update
sudo apt install g++ make mpg123 curl
```

### 2. Cloning & Compilation
```bash
# Clone the repository
git clone https://github.com/Abdul-Hadi-Munir/NEBULA-OS-V3.git
cd NEBULA-OS-V3

# Clean old builds and compile
make clean
make
```

### 3. Folder Preparation
NebulaOS requires specific folders to function:
*   `music/`: Place your `.mp3` files here.
*   `nebula_hdd/`: This is where your virtual files are saved.
*(Note: These are created automatically on the first run or by the setup script)*

---

## 🎮 Usage Instructions

### Starting the OS
Run the main binary:
```bash
./OS
```

### Configuration
On startup, you will be asked for:
1.  **RAM (GB):** Recommended 1-4 GB.
2.  **HDD (GB):** Recommended 5-20 GB.
3.  **Cores:** Recommended 2-8.

### Controls
*   **Numbers (1-23):** Launches a specific task.
*   **M:** Shows all running background/minimized tasks.
*   **F:** Bring a minimized task back to the foreground (requires PID).
*   **L:** View System Logs (Press 'C' to clear logs).
*   **Ctrl+Z:** Minimizes the current task to the background.
*   **0:** Graceful Shutdown.

---

## ❓ Troubleshooting & FAQ

**Q: Music player isn't playing sound.**  
**A:** Ensure `mpg123` is installed on your system. Check if your `.mp3` files are in the `music/` folder.

**Q: Task fails to launch.**  
**A:** Check the `L` (Logs) section. It's likely that the task requested more RAM than you have available. Close other tasks to free up memory.

**Q: How do I add my own songs?**  
**A:** Just drop any `.mp3` file into the `music/` directory. The Music Player will automatically detect it on the next launch.

---

**Developed by Abdul Hadi Munir**  
*NebulaOS V3: The Future of Minimalist Computing.*
