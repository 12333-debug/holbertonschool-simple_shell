#include "shell.h"

/**
 * builtin_env - prints the environment variables
 *
 * Return: 0 always
 */
int builtin_env(void)
{
    int i;

    for (i = 0; environ[i]; i++)
    {
        write(STDOUT_FILENO, environ[i], strlen(environ[i]));
        write(STDOUT_FILENO, "\n", 1);
    }

    return (0);
}
