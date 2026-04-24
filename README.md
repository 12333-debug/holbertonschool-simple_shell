# holbertonschool-simple_shell

## Description

This is a minimal Unix shell implemented for the Holberton School project.

`simple_shell` reads lines from standard input, parses them into arguments, searches for executables using the `PATH` environment variable, forks a child process and runs the requested program with `execve`. It follows project constraints: compiled with `-std=gnu89`, limited functions per file, include guards, and careful memory handling.

The shell uses `getline`, `strtok`, `fork`, `execve`, `waitpid`, `access`, and low-level I/O (`write`) for the prompt.

## Supported features

- Prompt printed when input is interactive (`$ `)  
- Read input with `getline`  
- Tokenize input into arguments with `strtok`  
- Resolve commands using `PATH` and `access`  
- Execute commands with `fork` + `execve` and wait with `waitpid`  
- Builtin: `exit` to quit the shell  
- Handles EOF (Ctrl-D) to exit cleanly

## Limitations

- No `cd` builtin in this minimal version  
- No pipes, redirections, or job control  
- No custom signal handling by default

## Compilation

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o simple_shell

## Author

Lonie Méïté
