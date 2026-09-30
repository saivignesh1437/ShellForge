# ShellForge

A simple Unix-like shell developed in C as part of the Operating Systems and System Programming project.

ShellForge demonstrates fundamental Linux/Unix system programming concepts including command parsing, dynamic memory management, process creation, and built-in commands.

---

## Project Progress

### Week 1 – REPL

- Interactive command prompt
- Basic user input handling
- Exit command
- Continuous Read-Evaluate-Print Loop

### Week 2 – Dynamic Memory

- Dynamic input buffer using `malloc()`
- Buffer expansion using `realloc()`
- Memory cleanup using `free()`
- Dynamic memory management for user input

### Week 3 – Command Parser

- Command parsing using `strtok()`
- Dynamic argument array
- NULL-terminated token array
- Parser modularization
- Separation of input and parsing functionality

### Week 4 – Process Execution

- Process creation using `fork()`
- Command execution using `execvp()`
- Parent-child synchronization using `waitpid()`
- Error handling using `perror()`
- External Linux command execution

### Week 5 – Built-in Commands

Implemented built-in commands:

- `cd` – Change directory
- `pwd` – Print working directory
- `help` – Display available commands
- `clear` – Clear the terminal
- `exit` – Exit ShellForge
- `env` – Display selected environment variables

Built-in commands execute directly inside the shell process.

External commands continue to use:

```text
fork()
  ↓
execvp()
  ↓
waitpid()
```

## Week 6 – Signals and Process Control

- Signal handling using `signal()`
- `SIGINT` support for Ctrl+C
- `SIGCHLD` handling for child process termination
- Zombie process cleanup using `waitpid()`
- Shell continues running after Ctrl+C

### Week 6 Testing

The following were tested:

- Normal command execution
- Child process execution using `sleep`
- Ctrl+C using `SIGINT`
- Shell continuation after Ctrl+C
- Zombie process checking using `ps`
- Child process cleanup

---

## Week 7 – Pipes and Inter-Process Communication

Implemented anonymous pipes using:

- `pipe()`
- `fork()`
- `dup2()`
- `execvp()`
- `waitpid()`

ShellForge currently supports **two-command pipelines**.

Example:

```text
command1 | command2
```

Example commands:

```bash
ls src | grep .c
echo hello | wc -w
```

### Pipe Implementation

The first child redirects its standard output to the pipe:

```c
dup2(pipefd[1], STDOUT_FILENO);
```

The second child redirects its standard input from the pipe:

```c
dup2(pipefd[0], STDIN_FILENO);
```

The parent closes unused pipe file descriptors and waits for both child processes.

### Week 7 Testing

Tested:

```bash
ls src | grep .c
```

```bash
echo hello | wc -w
```

```bash
echo hello world | wc -w
```

Verified:

- Successful communication between two processes
- Correct use of `pipe()`
- Correct use of `dup2()`
- Correct closing of pipe file descriptors
- Parent waiting for both child processes

---

## Week 8 – Memory Management, Debugging and Reliability

Week 8 focuses on improving the reliability of ShellForge using debugging and memory-analysis tools.

### Week 8 Features

- Memory leak detection using Valgrind
- Debugging using GDB
- AddressSanitizer build support
- Defensive programming practices
- Improved error handling
- Memory cleanup verification
- Verification of external command execution
- Verification of built-in command execution
- Verification of pipe execution

### Valgrind Testing

Valgrind was used with:

```bash
make clean
make
valgrind --leak-check=full ./bin/shellforge
```

Final result:

```text
All heap blocks were freed -- no leaks are possible
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

The final test reported:

```text
in use at exit: 0 bytes in 0 blocks
```

This verifies that the tested ShellForge execution completed without detected memory leaks.

### GDB Testing

GDB was used to test:

```text
break main
run
next
print line
backtrace
continue
quit
```

The debugging session verified:

- Program startup
- Breakpoint handling
- Step-by-step execution
- Variable inspection
- Call-stack inspection
- Program continuation

### AddressSanitizer

The Makefile provides an AddressSanitizer build target:

```bash
make asan
```

The project was compiled with:

```text
-fsanitize=address
```

Functional ShellForge commands were tested using the ASan build.

The execution environment produced a LeakSanitizer `ptrace` warning during termination. This was an environment/runtime limitation rather than a reported ShellForge memory error.

---

## Current Features

ShellForge currently supports:

- Interactive shell prompt
- Dynamic input handling
- Dynamic memory allocation
- Command parsing
- External command execution
- Built-in commands
- Environment variable access
- Signal handling
- Child process management
- Zombie process cleanup
- Two-command pipelines
- Memory leak testing
- GDB debugging
- AddressSanitizer build support
- Defensive error handling

---

## Example Usage

Start ShellForge:

```bash
./bin/shellforge
```

Example session:

```text
=====================================
ShellForge Version 4.0
=====================================

ShellForge> pwd
/home/user/Desktop/ShellForge

ShellForge> echo hello
hello

ShellForge> echo hello world
hello world

ShellForge> ls src | grep .c
builtin.c
input.c
main.c
parser.c
pipes.c
process.c
signals.c

ShellForge> echo hello | wc -w
1

ShellForge> exit
Goodbye!
```

---

## Build Instructions

### Compile the project

```bash
make
```

The executable is generated as:

```text
bin/shellforge
```

### Run ShellForge

```bash
make run
```

or:

```bash
./bin/shellforge
```

### Clean Build Files

```bash
make clean
```

### AddressSanitizer Build

```bash
make asan
```

---

## Project Structure

```text
ShellForge/
├── Makefile
├── README.md
│
├── include/
│   ├── shell.h
│   ├── input.h
│   ├── parser.h
│   ├── process.h
│   ├── builtin.h
│   ├── signals.h
│   └── pipes.h
│
├── src/
│   ├── main.c
│   ├── input.c
│   ├── parser.c
│   ├── process.c
│   ├── builtin.c
│   ├── signals.c
│   └── pipes.c
│
└── bin/
    └── shellforge
```

### Source Module Responsibilities

| Module | Responsibility |
|---|---|
| `main.c` | Main shell loop, command routing and pipe detection |
| `input.c` | Dynamic user input handling |
| `parser.c` | Command tokenization and token memory cleanup |
| `process.c` | External process creation and execution |
| `builtin.c` | Built-in shell commands |
| `signals.c` | Signal handling and child cleanup |
| `pipes.c` | Two-command pipeline implementation |
