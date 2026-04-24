#include "shell.h"

/**
 * execute_command - execute a command line (tokenize + PATH resolution)
 * @line: modifiable line (will be tokenized)
 */
void execute_command(char *line)
{
    pid_t pid;
    int status;
    char **argv;
    char *full_path = NULL;

    if (line == NULL)
        return;

    argv = split_line(line);
    if (!argv)
        return;

    if (!argv[0])
    {
        free(argv);
        return;
    }

    /* resolve path */
    full_path = find_path(argv[0]);
    if (!full_path)
    {
        /* command not found */
        dprintf(STDERR_FILENO, "%s: command not found\n", argv[0]);
        free(argv);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(full_path);
        free(argv);
        return;
    }

    if (pid == 0)
    {
        /* child */
        if (execve(full_path, argv, environ) == -1)
        {
            perror("execve");
            _exit(127);
        }
    }
    else
    {
        /* parent */
        waitpid(pid, &status, 0);
    }

    free(full_path);
    free(argv);
}
