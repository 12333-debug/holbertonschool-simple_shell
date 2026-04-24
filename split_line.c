#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

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
    while (token)
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
