#include "shell.h"

void execute_command(char *line)
{
    char **argv = split_line(line);
    char *path;
    pid_t pid;
    int status;

    if (!argv || !argv[0])
    {
        free(argv);
        return;
    }

    if (strcmp(argv[0], "env") == 0)
    {
        builtin_env();
        free(argv);
        return;
    }

    path = find_path(argv[0]);
    if (!path)
    {
        write(2, argv[0], strlen(argv[0]));
        write(2, ": command not found\n", 20);
        free(argv);
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        execve(path, argv, environ);
        perror(path);
        _exit(127);
    }
    else
    {
        waitpid(pid, &status, 0);
    }

    free(path);
    free(argv);
}
