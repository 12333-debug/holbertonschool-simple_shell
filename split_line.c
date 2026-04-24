#include "shell.h"

char **split_line(char *line)
{
    char **argv = NULL;
    char *token;
    int size = 0;

    argv = malloc(sizeof(char *) * 64);
    if (!argv)
        return (NULL);

    token = strtok(line, " ");
    while (token)
    {
        argv[size++] = token;
        token = strtok(NULL, " ");
    }
    argv[size] = NULL;

    return (argv);
}
