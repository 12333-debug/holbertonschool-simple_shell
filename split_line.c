#include "shell.h"

/**
 * split_line - Tokenize a command line into arguments
 * @line: input string to split
 * Return: array of tokens (argv)
 */
char **split_line(char *line)
{
    char **argv = malloc(sizeof(char *) * 64);
    char *token;
    int i = 0;

    if (!argv)
        return (NULL);

    token = strtok(line, " ");
    while (token)
    {
        argv[i++] = token;
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;

    return (argv);
}
