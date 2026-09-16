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

## Project Structure

```text
ShellForge/
├── include/
│   ├── builtin.h
│   ├── input.h
│   ├── parser.h
│   ├── process.h
│   └── shell.h
├── src/
│   ├── builtin.c
│   ├── input.c
│   ├── main.c
│   ├── parser.c
│   └── process.c
├── data/
├── Makefile
├── README.md
└── .gitignore
