#include "shell.h"

/**
 * display_prompt - Print "$ " only in interactive mode
 */
void display_prompt(void)
{
    if (isatty(0))
        write(1, "$ ", 2);
}
