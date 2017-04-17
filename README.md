## Simple Shell
### Description
Simple Recreation of command-line shell.

## Repo Contents

|   **File**    |  **Decription**                       |
|---------------|---------------------------------------|
|  `shell.h`	|  Header file: contains prototypes	|
|  `sh-main.c`	|  Main file		 		|
|  `builtins.c` |  Functions to execute builtins	|
|  `env_list.c` |  Environmental variable list		|
|  `env_cmd.c`	|  Functions for getenv, setenv, unsetenv|
|  `free_func.c`  |  Function to free memory		   |
|  `helper_func.c`  | Helper functions: custom realloc   |
|  `path.c`	|  Implements the PATH	       		|

### How to Use
* Clone repo
```
git clone https://github.com/lisale0/simple_shell.git
```
Compile all the `.c` files in /simple_shell
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
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
### Authors
*Lisa Leung* - [Github](https://github.com/lisale0) || [Twitter](https://twitter.com/lisale01) || [email](lisa.leung@holbertonschool.com)

*Joe McDaniel* - [Github](https://github.com/joseph-mcdaniel) || [Twitter](https://twitter.com/joe_w_mcdaniel) || [email](joseph.mcdaniel@holbertonschool.com)