#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"
#include "../include/pipes.h"

int main()
{
    char *line;
    char **tokens;

    /*
     * Initialize signal handling
     * Week 6:
     * - SIGINT  -> Ctrl+C
     * - SIGCHLD -> child process cleanup
     */
    initialize_signals();

    printf("=====================================\n");
    printf("ShellForge Version 4.0\n");
    printf("=====================================\n");

    while (1)
    {
        printf("ShellForge> ");

        /*
         * Read command from user
         */
        line = read_line();

        /*
         * Handle exit command
         */
        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        /*
         * Parse command into tokens
         */
        tokens = parse_line(line);

        /*
         * Execute command if tokens are available
         */
        if (tokens[0] != NULL)
        {
            int pipe_index = -1;

            /*
             * Search for pipe symbol '|'
             */
            for (int i = 0; tokens[i] != NULL; i++)
            {
                if (strcmp(tokens[i], "|") == 0)
                {
                    pipe_index = i;
                    break;
                }
            }

            /*
             * Week 7:
             * Two-command pipeline
             */
            if (pipe_index != -1)
            {
                char **cmd1 = tokens;
                char **cmd2 = &tokens[pipe_index + 1];

                /*
                 * Separate the two commands
                 */
                tokens[pipe_index] = NULL;

                /*
                 * Make sure both commands exist
                 */
                if (cmd1[0] != NULL && cmd2[0] != NULL)
                {
                    execute_pipe(cmd1, cmd2);
                }
                else
                {
                    printf("ShellForge: invalid pipe command\n");
                }
            }
            else
            {
                /*
                 * No pipe.
                 * First check for built-in commands.
                 */
                if (execute_builtin(tokens) == 0)
                {
                    /*
                     * Execute external command
                     */
                    execute(tokens);
                }
            }
        }

        /*
         * Free allocated memory
         */
        free_tokens(tokens);
        free(line);
    }

    printf("Goodbye!\n");

    return 0;
}
