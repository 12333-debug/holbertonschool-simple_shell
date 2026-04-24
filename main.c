#include "shell.h"

/**
 * main - main loop of the mini shell
 *  Reads input lines, handles the simple builtin "exit",
 *  and launches external commands by delegating to execute_command.
 *
 *  Return: 0 on normal exit
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
			/* EOF (Ctrl-D) ou erreur de lecture */
			if (line)
				free(line);
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* supprimer le '\n' final si présent */
		if (nread > 0 && line[nread - 1] == '\n')
			line[nread - 1] = '\0';

		/* ignorer ligne vide */
		if (line[0] == '\0')
			continue;

		/* builtin minimal pour quitter */
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			break;
		}

		execute_command(line);
	}

	return (0);
}
