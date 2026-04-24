#include "shell.h"

/**
 * execute_command - execute a command line (tokenize + PATH resolution)
 * @line: modifiable line (will be tokenized)
 */
void execute_command(char *line)
{
    pid_t pid;
    int status;
    char **argv;
    char *full_path = NULL;
    int j;

    if (line == NULL)
        return;

    argv = split_line(line);
    if (!argv)
        return;
	
    if (!argv[0])
    {
        free(argv);
        return;
    }

	if (strcmp(argv[0], "env") == 0)
    {
        builtin_env();   /* affiche toutes les variables */
        free(argv);      /* libère argv */
        return;          /* surtout pas fork */
    }

    /* resolve path */
    full_path = find_path(argv[0]);
    if (!full_path)
    {
        /* command not found */
        fprintf(stderr, "%s: command not found\n", argv[0]);
        free(argv);
        return;
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        free(full_path);
        free(argv);
        return;
    }

    if (pid == 0)
    {
        /* child */
        if (execve(full_path, argv, environ) == -1)
        {
            /* affiche l'erreur système liée au chemin exact */
            perror(full_path);
            _exit(127);
        }
    }
    else
    {
        /* parent */
        waitpid(pid, &status, 0);
    }

    free(full_path);
    free(argv);
}
