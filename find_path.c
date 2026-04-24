#include "shell.h"

static char *_strdup(const char *s)
{
    char *p;
    size_t len = strlen(s);

    p = malloc(len + 1);
    if (!p)
        return (NULL);

    strcpy(p, s);
    return (p);
}

char *find_path(char *cmd)
{
    char *path_env = NULL, *copy, *dir, *full;
    int i;

    if (strchr(cmd, '/'))
    {
        if (access(cmd, 0) == 0)
            return (_strdup(cmd));
        return (NULL);
    }

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path_env = environ[i] + 5;
            break;
        }
    }

    if (!path_env)
        return (NULL);

    copy = _strdup(path_env);
    if (!copy)
        return (NULL);

    dir = strtok(copy, ":");
    while (dir)
    {
        full = malloc(strlen(dir) + strlen(cmd) + 2);
        if (!full)
        {
            free(copy);
            return (NULL);
        }

        strcpy(full, dir);
        strcat(full, "/");
        strcat(full, cmd);

        if (access(full, 0) == 0)
        {
            free(copy);
            return (full);
        }

        free(full);
        dir = strtok(NULL, ":");
    }

    free(copy);
    return (NULL);
}
