<p align="center">
  <img src="https://github.com/ayogun/42-project-badges/raw/main/badges/pipexe.png" alt="Pipex Badge" width="150" height="150">
</p>

## 📖 About

"pipex" is a project at 42 Madrid that involves recreating the shell pipe functionality (`|`) and redirection operators (`<`, `>`) in C. This project introduces process management, inter-process communication, file descriptors manipulation, and teaches how to handle command execution in a systematic way.

The goal is to implement a program that mimics the behavior of shell pipes, taking an input file, executing two commands in sequence where the output of the first becomes the input of the second, and writing the final result to an output file.

## 🎯 Objectives

- Understanding and implementing pipes and redirection in C
- Learning about process creation and management with fork()
- Managing file descriptors and their duplication
- Implementing inter-process communication mechanisms
- Handling command execution and path resolution
- Managing edge cases and error handling

## 📋 Function Overview

<details>
<summary><strong>pipex</strong></summary>

### Concepts

**Description:** Program that simulates shell pipe functionality  
**Usage:** `./pipex infile cmd1 cmd2 outfile`  
**Equivalent:** `< infile cmd1 | cmd2 > outfile`  

```c
int main(int argc, char **argv, char **envp);
```

### Use of pipes and process management
The implementation of **pipex** requires creating processes and establishing communication between them. For this, several system calls are used:

The main system calls are:

- **`pipe()`** ➜ Creates a unidirectional communication channel between processes. Returns two file descriptors: one for reading and one for writing.

```c
int pipefd[2];
pipe(pipefd);
```

- **`fork()`** ➜ Creates a child process that is an exact copy of the parent process.

```c
pid_t pid = fork();
```

- **`dup2()`** ➜ Duplicates a file descriptor, allowing redirection of input/output streams.

```c
dup2(pipefd[1], STDOUT_FILENO);
```

- **`execve()`** ➜ Replaces the current process image with a new program.

```c
execve(cmd_path, cmd_args, envp);
```

- **`waitpid()`** ➜ Waits for a specific child process to change state.

```c
waitpid(pid, &status, 0);
```

These system calls are essential for implementing **pipex**, as they allow process management, inter-process communication, and command execution.

</details>

<details>
<summary><strong>Mandatory Requirements</strong></summary>

### Program Behavior

- **Input:** `./pipex infile cmd1 cmd2 outfile`
- **Equivalent shell command:** `< infile cmd1 | cmd2 > outfile`
- **Function:** Takes 4 arguments where:
  - `infile`: Input file to read from
  - `cmd1`: First command to execute
  - `cmd2`: Second command to execute  
  - `outfile`: Output file to write to

### Examples

```bash
# Example 1
./pipex infile "ls -l" "wc -l" outfile
# Equivalent to: < infile ls -l | wc -l > outfile

# Example 2  
./pipex infile "grep a1" "wc -w" outfile
# Equivalent to: < infile grep a1 | wc -w > outfile
```

</details>

## 🚀 Installation & Structure

<details>
<summary><strong>📥 Download & Compilation</strong></summary>
    
<br>

```bash
# Clone the repository
git clone https://github.com/ravazque/pipex.git
cd pipex

# Compile the program
make

# Clean object files
make clean

# Clean everything including executable
make fclean

# Recompile everything
make re

# Run the program
./pipex infile "command1" "command2" outfile
```

<br>

</details>

<details>
<summary><strong>📁 Project Structure</strong></summary>

<br>

```
pipex/
├──┬ include/
│  └── pipex.h                          # Header file with prototypes and definitions
├──┬ src/
│  ├── pipex.c                          # Main program implementation
│  ├── pipex_utils.c                    # Utility functions for path resolution
│  ├── pipex_process.c                  # Process management functions
│  └── pipex_errors.c                   # Error handling functions
├── Makefile                            # Compilation rules
└── README.md                           # Project documentation
```

<br>

</details>

## 💡 Key Learning Outcomes

The pipex project teaches advanced UNIX system programming concepts:

- **Process Management**: Understanding fork(), execve(), and wait() system calls
- **Inter-Process Communication**: Learning to create and manage pipes between processes
- **File Descriptor Manipulation**: Deep knowledge of dup2() and file redirection
- **Command Execution**: Learning to resolve command paths and execute programs
- **Error Handling**: Proper management of system call failures and edge cases
- **UNIX Philosophy**: Understanding how shell pipes work under the hood

## ⚙️ Technical Specifications

- **Language**: C (C99 standard)
- **Compiler**: cc with flags `-Wall -Wextra -Werror`
- **System Calls**: pipe(), fork(), execve(), dup2(), close(), wait(), access()
- **Dependencies**: Only standard C library and system calls
- **Platform**: UNIX-like systems (Linux, macOS)
- **Memory Management**: Proper cleanup of resources and file descriptors
- **Process Handling**: Parent-child process synchronization

---

> [!NOTE]
> This project serves as an introduction to UNIX system programming and demonstrates proficiency in process management and inter-process communication concepts.