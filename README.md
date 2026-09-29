# ShellForge

A simple Unix-like shell developed in C as part of the Operating Systems and System Programming project.

## Project Progress

### Week 1 – REPL
- Interactive command prompt
- Basic input handling
- Exit command

### Week 2 – Dynamic Memory
- Dynamic input buffer using malloc()
- Buffer expansion using realloc()
- Memory cleanup using free()

### Week 3 – Command Parser
- Command parsing using strtok()
- Dynamic argv[] creation
- NULL-terminated token array
- Parser modularization

### Week 4 – Process Execution
- Process creation using fork()
- Command execution using execvp()
- Parent-child synchronization using waitpid()
- Error handling using perror()

### Week 5 – Built-in Commands
- Built-in commands: cd, pwd, help, clear, exit
- Environment variable support using getenv()
- env command
- Built-in commands execute directly inside the shell
- External commands continue to use fork(), execvp(), and waitpid()

### Week 6 – Signals and Process Control
- Signal handling using signal()
- SIGINT support for Ctrl+C
- SIGCHLD support for child process termination
- Zombie process cleanup using waitpid()
- Shell continues running after Ctrl+C

## Week 6 Testing

- Successfully compiled using Makefile
- Tested normal command execution
- Tested child process execution using sleep
- Tested Ctrl+C using SIGINT
- Verified that ShellForge remains active after Ctrl+C
- Checked for zombie processes using ps -el
- No zombie processes were found

## Project Structure

```text
ShellForge/
├── README.md
├── Makefile
├── bin/
├── include/
│   ├── shell.h
│   ├── input.h
│   ├── parser.h
│   ├── process.h
│   ├── builtin.h
│   └── signals.h
└── src/
    ├── main.c
    ├── input.c
    ├── parser.c
    ├── process.c
    ├── builtin.c
    └── signals.c
