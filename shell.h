#ifndef SHELL_H
#define SHELL_H

/* includes autorisés */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/stat.h>

/* prototypes */

/* affiche le prompt */
void display_prompt(void);

/* découpe la ligne en tokens (argv) */
char **split_line(char *line);

/* cherche la commande dans PATH, retourne un chemin malloc'd ou NULL */
char *find_path(char *cmd);

/* exécute la commande (gère fork/execve/wait) */
void execute_command(char *line);

#endif /* SHELL_H */
