#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

extern char **environ;

char *trim_spaces(char *s)
{
    char *end;

    while (*s == ' ' || *s == '\t')
        s++;

    if (*s == '\0')
        return s;

    end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return s;
}

int main(int argc, char **argv)
{
    char *line = NULL;
    char *trimmed;
    char **args;
    char *cmd_path;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    int last_status = 0;
    int interactive = isatty(STDIN_FILENO);

    (void)argc;

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, ":) ", 3);

        nread = getline(&line, &len, stdin);
        if (nread == -1)
            break;

        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        trimmed = trim_spaces(line);
        if (trimmed[0] == '\0')
            continue;

        args = split_line(trimmed);
        if (!args)
            continue;

        /* Built-in exit */
        if (strcmp(args[0], "exit") == 0)
        {
            free(args);
            free(line);
            exit(last_status);
        }

        cmd_path = find_in_path(args[0]);
        if (!cmd_path)
        {
            fprintf(stderr, "%s: command not found\n", argv[0]);
            free(args);
            continue;
        }

        pid = fork();
        if (pid == -1)
        {
            perror(argv[0]);
            free(args);
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            execve(cmd_path, args, environ);
            perror(argv[0]);
            exit(EXIT_FAILURE);
        }
        else
        {
            waitpid(pid, &status, 0);

            if (WIFEXITED(status))
                last_status = WEXITSTATUS(status);
        }

        if (cmd_path != args[0])
            free(cmd_path);

        free(args);
    }

    free(line);
    return last_status;
}
