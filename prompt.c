#include "shell.h"

/**
 * display_prompt - print prompt if input is interactive
 */
void display_prompt(void)
{
	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "$ ", 2);
}
