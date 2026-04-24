#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

/* rendre environ accessible depuis les .c */
extern char **environ;

/* prototypes des fonctions du mini-shell */
void display_prompt(void);
char **split_line(char *line);
char *find_path(char *cmd);
void execute_command(char *line);

#endif
