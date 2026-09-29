#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int execute(char **tokens)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0)
    {
        /*
         * Child process
         */
        if (execvp(tokens[0], tokens) == -1)
        {
            perror("ShellForge");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        /*
         * fork() failed
         */
        perror("ShellForge");
        return 1;
    }
    else
    {
        /*
         * Parent process
         *
         * Wait for the foreground child.
         * The SIGCHLD handler may have already
         * collected the child, so handle ECHILD.
         */
        while (1)
        {
            pid_t result = waitpid(pid, &status, WUNTRACED);

            if (result == pid)
            {
                /*
                 * Child was successfully collected.
                 */
                if (WIFEXITED(status) || WIFSIGNALED(status))
                {
                    break;
                }
            }
            else if (result == -1)
            {
                /*
                 * SIGCHLD handler may have already
                 * reaped the child.
                 */
                if (errno == EINTR)
                {
                    continue;
                }

                if (errno == ECHILD)
                {
                    break;
                }

                perror("waitpid");
                break;
            }
        }
    }

    return 1;
}
