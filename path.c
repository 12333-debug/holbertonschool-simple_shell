#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

extern char **environ;

char *find_in_path(char *cmd)
{
    char *path = NULL;
    char *copy, *dir, *full;
    int i, len;

    /* If command is absolute or relative path */
    if (cmd[0] == '/' || cmd[0] == '.')
        return cmd;

    /* Find PATH manually in environ */
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = environ[i] + 5;
            break;
        }
    }

    /* No PATH variable → command cannot be found */
    if (!path || path[0] == '\0')
        return NULL;

    copy = strdup(path);
    if (!copy)
        return NULL;

    dir = strtok(copy, ":");
    while (dir)
    {
        len = strlen(dir) + strlen(cmd) + 2;
        full = malloc(len);
        if (!full)
        {
            free(copy);
            return NULL;
        }

        sprintf(full, "%s/%s", dir, cmd);

        if (access(full, X_OK) == 0)
        {
            free(copy);
            return full;
        }

        free(full);
        dir = strtok(NULL, ":");
    }

    free(copy);
    return NULL;
}
