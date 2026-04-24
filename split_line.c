#include "shell.h"

/**
 * split_line - split a modifiable line into tokens
 * @line: modifiable string (buffer from getline)
 *
 * Return: malloc'd array of pointers terminated by NULL, or NULL on error
 * Note: tokens point inside line; free(argv) is enough to free the array.
 */
char **split_line(char *line)
{
	char *token;
	char **argv;
	int count = 0, i = 0;
	char *p;

	if (line == NULL)
		return (NULL);

	/* count tokens */
	p = line;
	while (*p)
	{
		while (*p == ' ' || *p == '\t')
			p++;
		if (*p == '\0')
			break;
		count++;
		while (*p && *p != ' ' && *p != '\t')
			p++;
	}

	if (count == 0)
		return (NULL);

	argv = malloc((count + 1) * sizeof(char *));
	if (!argv)
		return (NULL);

	token = strtok(line, " \t");
	while (token != NULL)
	{
		argv[i++] = token;
		token = strtok(NULL, " \t");
	}
	argv[i] = NULL;

	return (argv);
}
