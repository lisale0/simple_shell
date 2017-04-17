## Simple Shell
### Description
Simple Recreation of command-line shell.
### Function and System Calls Utilized
* `access`
* `chdir`
* `close`
* `closedir`
* `execve`
* `exit`
* `fork`
* `free`
* `fstat`
* `getcwd`
* `getline`
* `kill`
* `lstat`
* `malloc`
* `open`
* `opendir`
* `perror`
* `read`
* `readdir`
* `signal`
* `stat`
* `wait`
* `waitpid`
* `wait3`
* `wait4`
* `write`
* `_exit`
### Compilation
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
### File Description
* `shell.h`

  Prototypes, macros, and structs

* `builtins.c`

  Function to execute builtins

* `env_list.c`

  Environmental variable list

* `env_cmd.c`

 Functions for getenv, setenv, unsetenv

* `free_func.c`

  Function to free space

* `helper_func.c`

  Custom realloc function

* `path.c`

  Implements the PATH

### Authors

Lisa Leung
Joe McDaniel