#include "shell.h"

/**
 * main - Entry point of the simple shell
 * Return: 0 on success
 */
int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t n;

    while (1)
    {

        display_prompt();  /* Affiche le prompt uniquement en mode interactif */

        n = getline(&line, &len, stdin);/* Lit la ligne entrée par l'utilisateur */
        if (n == -1)
        {
            /* Ctrl+D ou erreur */
            free(line);
            write(1, "\n", 1);
            break;
        }

        if (line[n - 1] == '\n')/* Retire le \n final */
            line[n - 1] = '\0';

        if (strcmp(line, "exit") == 0)
        {
            free(line);
            break;
        }

        execute_command(line); /*execute la commande*/
    }

    return (0);
}