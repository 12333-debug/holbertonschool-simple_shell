#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;

/* Remove leading/trailing spaces */
char *trim_spaces(char *s)
{
    while (*s == ' ' || *s == '\t')
        s++;

    if (*s == '\0')
        return s;

    char *end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\t'))
        end--;

    *(end + 1) = '\0';
    return s;
}

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

        nread = getline(&line, &len, stdin);
        if (nread == -1) /* EOF */
            break;

        /* Remove newline */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Trim spaces */
        char *cmd = trim_spaces(line);

        /* Ignore empty or spaces-only lines */
        if (cmd[0] == '\0')
            continue;

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
            cmd_argv[0] = cmd;
            cmd_argv[1] = NULL;

            if (execve(cmd, cmd_argv, environ) == -1)
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
