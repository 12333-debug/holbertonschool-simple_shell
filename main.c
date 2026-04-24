#include "shell.h"

/**
 * main - main loop of the mini shell
 * Return: 0
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1)
    {
        display_prompt();

        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            free(line);
            write(STDOUT_FILENO, "\n", 1);
            break;
        }

        if (nread > 0 && line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        if (line[0] == '\0')
            continue;

        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        execute_command(line);
    }

    return (0);
}
