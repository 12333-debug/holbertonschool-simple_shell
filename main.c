#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    pid_t pid;
    int status;
    int interactive = isatty(STDIN_FILENO);

    (void)argc;

    while (1)
    {
        if (interactive)
            write(STDOUT_FILENO, "($) ", 4);

        /* Read user input */
        nread = getline(&line, &len, stdin);
        if (nread == -1) /* EOF (Ctrl+D) */
            break;

        /* Ignore empty line */
        if (nread == 1 && line[0] == '\n')
            continue;

        /* Remove newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        pid = fork();
        if (pid == -1)
        {
            perror(argv[0]);
            free(line);
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            char *cmd_argv[2];

            cmd_argv[0] = line;
            cmd_argv[1] = NULL;

            /* No PATH handling: execve only what user typed */
            if (execve(line, cmd_argv, environ) == -1)
            {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }
    }

    free(line);
    return 0;
}
