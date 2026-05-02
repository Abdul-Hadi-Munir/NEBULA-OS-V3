# NEBULA OS V3 🚀
**A Minimalist High-Performance Operating System Simulator**

NebulaOS V3 is a sophisticated CLI-based operating system simulator designed to demonstrate core OS concepts including multi-level queue scheduling, resource management, inter-process communication (IPC), and multitasking within a minimalist terminal environment.

---

## 🌟 Key Features

### 🧠 Advanced Kernel Architecture
*   **Multi-Level Queue Scheduling:** 
    *   **Q0 (Priority Queue):** Real-time and high-priority tasks.
    *   **Q1 (Round Robin):** Balanced time-sharing for interactive applications.
    *   **Q2 (FCFS):** Batch processing for background services.
*   **Dynamic Resource Management:** Real-time tracking of RAM, HDD, and CPU cores.
*   **Inter-Process Communication (IPC):** Robust messaging system using named pipes (FIFOs).
*   **Deadlock Detection:** Automated monitoring to prevent resource starvation.

### 💼 Integrated Productivity Suite (23 Built-in Tasks)
*   **Professional Notepad:** Vim-style commands (`:w`, `:wq`), autosave, and large buffer support.
*   **Enhanced Music Player:** MP3 playback support via `mpg123` with song selection from a local library.
*   **System Tools:** Task Manager, Resource Monitor, Log Viewer, and Mini Terminal.
*   **Productivity:** Calendar, Alarm/Reminder (with background daemon support), To-Do List, and Stopwatch.
*   **File Management:** Create, Delete, Move, Copy, Rename, and File Info tools.
*   **Games & Fun:** Number Guesser (Space Theme) and Comic-style Dice Roller.

### 🛡️ System Integrity
*   **Background Daemons:** Services like the Clock and Log Daemon run silently in the background.
*   **Process Isolation:** Each task runs as an independent process with controlled resource allocation.
*   **Minimalist UI:** High-quality, distraction-free terminal interface with box headers and consistent formatting.

---

## 🛠️ Technical Stack
*   **Language:** C++17
*   **Concurrency:** POSIX Threads (pthreads)
*   **Signals:** Unix Signal Handling (`SIGTSTP`, `SIGCONT`, `SIGUSR1`, etc.)
*   **I/O:** Non-blocking terminal I/O using `select()` and `termios`.
*   **Audio:** Integration with `mpg123` for MP3 playback.

---

## 🚀 Getting Started

### Prerequisites
*   `g++` (C++17 support)
*   `make`
*   `mpg123` (for Music Player functionality)

### Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/Abdul-Hadi-Munir/NEBULA-OS-V3.git
   cd NEBULA-OS-V3
   ```
2. Build the system:
   ```bash
   make
   ```

### Running the OS
Launch the main kernel:
```bash
./OS
```
Follow the on-screen prompts to configure your system resources (RAM, HDD, Cores) and start exploring the Nebula dashboard.

---

## 📁 Project Structure
```text
NebulaOS/
├── src/                # Core Source Code
│   ├── kernel/         # OS Kernel (Scheduler, Memory, IPC)
│   ├── tasks/          # Built-in Applications
│   └── os.cpp          # Main Entry Point
├── include/            # Header Files
├── music/              # MP3 Library
├── nebula_hdd/         # Virtual Hard Drive Storage
├── Makefile            # Build System
└── README.md           # Documentation
```

---

## 📜 Development Notes
NebulaOS V3 prioritizes **Professionalism** and **Minimalism**. All code is written for high performance with zero unnecessary overhead. Emojis are used selectively in games and fun tools, while system utilities maintain a sleek, technical aesthetic.

---

## 🤝 Contributing
NebulaOS is an educational project. Feel free to fork, submit PRs, or report issues to help improve the simulation.

**Developed by Abdul Hadi Munir**
