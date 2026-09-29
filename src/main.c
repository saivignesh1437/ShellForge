#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell.h"
#include "../include/input.h"
#include "../include/parser.h"
#include "../include/process.h"
#include "../include/builtin.h"
#include "../include/signals.h"

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
            /*
             * First check for built-in commands.
             *
             * execute_builtin() returns:
             * 0 -> command was a built-in
             * non-zero -> command is not a built-in
             */
            if (execute_builtin(tokens) != 0)
            {
                /*
                 * Execute external command
                 */
                execute(tokens);
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
