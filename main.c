#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

extern char **environ;

/* Trim leading and trailing spaces */
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

/* Split line into tokens */
char **split_line(char *line)
{
    char **tokens;
    char *token;
    int bufsize = 64;
    int i = 0;

    tokens = malloc(sizeof(char *) * bufsize);
    if (!tokens)
        return NULL;

    token = strtok(line, " \t");
    while (token != NULL)
    {
        tokens[i] = token;
        i++;

        if (i >= bufsize)
        {
            bufsize += 64;
            tokens = realloc(tokens, sizeof(char *) * bufsize);
            if (!tokens)
                return NULL;
        }

        token = strtok(NULL, " \t");
    }

    tokens[i] = NULL;
    return tokens;
}

int main(int argc, char **argv)
{
    char *line = NULL;
    char *trimmed;
    char **args;
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

        pid = fork();
        if (pid == -1)
        {
            perror(argv[0]);
            free(args);
            free(line);
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execve(args[0], args, environ) == -1)
            {
                perror(argv[0]);
                free(args);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            waitpid(pid, &status, 0);
        }

        free(args);
    }

    free(line);
    return 0;
}
