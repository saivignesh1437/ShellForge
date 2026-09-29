#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * SIGINT handler
 * Handles Ctrl+C
 */
static void sigint_handler(int sig)
{
    (void)sig;

    printf("\nShellForge: Press 'exit' to quit.\n");
    printf("ShellForge> ");
    fflush(stdout);
}

/*
 * SIGCHLD handler
 * Cleans up terminated child processes
 * and prevents zombie processes.
 */
static void sigchld_handler(int sig)
{
    (void)sig;

    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
        /* Keep collecting terminated children */
    }
}

/*
 * Initialize all signal handlers
 */
void initialize_signals(void)
{
    signal(SIGINT, sigint_handler);
    signal(SIGCHLD, sigchld_handler);
}
