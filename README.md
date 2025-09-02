# Penguin Shell 🐧

Do you like Penguins? Then you might like this too.  
Penguin is a simple **POSIX-like shell** written in C. It supports basic command execution, some built-in UNIX commands, and is designed as a fun practice project to learn more about system calls and POSIX features.

---

## Features
- Run external programs via `fork` and `exec`.
- Built-in commands like `cd` and `exit`.
- Path resolution with support for `~`, `.`, and `..`.
- Simple Makefile build system.

---

## Installation

Clone the repository:

```bash
git clone https://github.com/lucky017/penguin.git
cd penguin
```
Compile and Run the executable (penguin):
```bash
make compile
make run  or ./penguin
```
---

### Usage

Once inside Penguin Shell, you can type commands like:
```bash
ls   - to list the files and directories 
cd   - to change the current working directory
exit - to exit the shell
```
You can use the special characters like:
```bash
.   - specifies the current working directory
..  - specifies the parent directory
```
--- 

### Notes
- Requires gcc and make.
- Tested on Linux (POSIX-compliant systems).
