#include "shell.h"

/**
 * find_path - search for cmd in PATH
 * Return: malloc'd full path or NULL
 */
char *find_path(char *cmd)
{
    char *path_env = NULL, *path_copy = NULL;
    char *path_dir, *try_path;
    size_t dir_len, cmd_len;
    int i;

    if (!cmd)
        return (NULL);

    if (strchr(cmd, '/'))
    {
        if (access(cmd, X_OK) == 0)
            return (strdup(cmd));
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

    path_copy = strdup(path_env);
    if (!path_copy)
        return (NULL);

    cmd_len = strlen(cmd);
    path_dir = strtok(path_copy, ":");

    while (path_dir)
    {
        dir_len = strlen(path_dir);
        try_path = malloc(dir_len + 1 + cmd_len + 1);
        if (!try_path)
        {
            free(path_copy);
            return (NULL);
        }

        strcpy(try_path, path_dir);
        try_path[dir_len] = '/';
        try_path[dir_len + 1] = '\0';
        strcat(try_path, cmd);

        if (access(try_path, X_OK) == 0)
        {
            free(path_copy);
            return (try_path);
        }

        free(try_path);
        path_dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}
