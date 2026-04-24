#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

extern char **environ;

char *find_in_path(char *cmd)
{
    char *path, *copy, *dir, *full;
    int len;

    if (cmd[0] == '/' || cmd[0] == '.')
        return cmd;

    path = getenv("PATH");
    if (!path)
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
