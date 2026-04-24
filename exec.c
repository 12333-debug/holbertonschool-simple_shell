#include "shell.h"

/**
 * execute_command - tokenize + PATH + exec
 */
void execute_command(char *line)
{
    pid_t pid;
    int status;
    char **argv;
    char *full_path = NULL;

    if (!line)
        return;

    argv = split_line(line);
    if (!argv)
        return;

    if (!argv[0])
    {
        free(argv);
        return;
    }

    /* built-in env */
    if (strcmp(argv[0], "env") == 0)
    {
        builtin_env();
        free(argv);
        return;
    }

    /* PATH resolution */
    full_path = find_path(argv[0]);
    if (!full_path)
    {
        fprintf(stderr, "%s: command not found\n", argv[0]);
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
        if (execve(full_path, argv, environ) == -1)
        {
            perror(full_path);
            _exit(127);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(full_path);
    free(argv);
}
