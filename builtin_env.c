#include "shell.h"

/**
 * builtin_env - Print all environment variables
 * Return: always 0
 */
int builtin_env(void)
{
    int i;

    for (i = 0; environ[i]; i++)
    {
        write(1, environ[i], strlen(environ[i]));
        write(1, "\n", 1);
    }

    return (0);
}
