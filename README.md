# Shell
### Description
This project is a recreation of the command-line interpreter (shell).
In terms of functionality, it mirrors `sh` in a limited scope.
### Synopsis
This version of the shell has a collection of custom built-in commands along
with the functionality of running scripts in the the various paths on a given operating system.
### Environment
Our Shell has been tested on Ubuntu 14.05.5 LTS.
Tests done in VirtualBox on [Ubuntu](https://atlas.hashicorp.com/ubuntu/boxes/trusty64) via [Vagrant](https://www.vagrantup.com/)(1.9.1)

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
|  `prompt_hlp.c`  | Prompt helper functions		|

### How to Use
Clone repo
```
git clone https://github.com/lisale0/simple_shell.git
```
Change directory to simple_shell
```
cd simple_shell/
```
Compile all the `.c` files in /simple_shell
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```

### Interactive and Non-Interactive Mode
In interactive mode is character input is accepted from character input.
```
$ ./hsh
$ ls -l
total 108
-rw-r--r-- 1 vagrant vagrant   179 Apr 19 08:05 AUTHORS
-rwxr-xr-x 1 vagrant vagrant  2837 Apr 20 03:36 README.md
-rwxr-xr-x 1 vagrant vagrant  2471 Apr 19 22:13 builtins.c
-rwxr-xr-x 1 vagrant vagrant  2123 Apr 20 03:28 env_cmd.c
-rwxr-xr-x 1 vagrant vagrant  1866 Apr 20 03:29 env_list.c
-rwxr-xr-x 1 vagrant vagrant   816 Apr 19 22:15 free_func.c
-rwxr-xr-x 1 vagrant vagrant  3225 Apr 19 22:28 helper_func.c
-rwxr-xr-x 1 vagrant vagrant 31912 Apr 19 22:24 hsh
-rwxr--r-- 1 vagrant vagrant     6 Apr 20 04:13 ls
-rw-r--r-- 1 vagrant vagrant  3648 Apr 20 03:36 man_1_simple_shell
-rwxr-xr-x 1 vagrant vagrant  1594 Apr 19 18:26 path.c
-rwxr-xr-x 1 vagrant vagrant  2210 Apr 19 22:30 prompt_hlp.c
-rwxr-xr-x 1 vagrant vagrant  2674 Apr 19 18:25 sh-main.c
-rwxr-xr-x 1 vagrant vagrant  4098 Apr 19 22:59 shell.h
-rwxr-xr-x 1 vagrant vagrant  1639 Apr 19 08:05 str_hlp.c
$ echo hello
hello
$ 
```
However, the shell is designed to have the capability to run in non-interactive mode.

In non-interactive mode, the shell is run from a script or something similar.
The subshell only opens when the script is executed and subsequently closes
once the script is finished.
```
$ cat script
ls -l
$ cat script | ./hsh
total 108
-rw-r--r-- 1 vagrant vagrant   179 Apr 19 08:05 AUTHORS
-rwxr-xr-x 1 vagrant vagrant  2837 Apr 20 03:36 README.md
-rwxr-xr-x 1 vagrant vagrant  2471 Apr 19 22:13 builtins.c
-rwxr-xr-x 1 vagrant vagrant  2123 Apr 20 03:28 env_cmd.c
-rwxr-xr-x 1 vagrant vagrant  1866 Apr 20 03:29 env_list.c
-rwxr-xr-x 1 vagrant vagrant   816 Apr 19 22:15 free_func.c
-rwxr-xr-x 1 vagrant vagrant  3225 Apr 19 22:28 helper_func.c
-rwxr-xr-x 1 vagrant vagrant 31912 Apr 19 22:24 hsh
-rwxr--r-- 1 vagrant vagrant     6 Apr 20 04:13 ls
-rwxr--r-- 1 vagrant vagrant    18 Apr 20 04:12 ls~
-rw-r--r-- 1 vagrant vagrant  3648 Apr 20 03:36 man_1_simple_shell
-rwxr-xr-x 1 vagrant vagrant  1594 Apr 19 18:26 path.c
-rwxr-xr-x 1 vagrant vagrant  2210 Apr 19 22:30 prompt_hlp.c
-rwxr-xr-x 1 vagrant vagrant  2674 Apr 19 18:25 sh-main.c
-rwxr-xr-x 1 vagrant vagrant  4098 Apr 19 22:59 shell.h
-rwxr-xr-x 1 vagrant vagrant  1639 Apr 19 08:05 str_hlp.c
```

### Builtins and commands
Below are list of some of the more prominent commands used, for further
information refer to the man page - to access in your terminal type:
```
man ./man_1_simple_shell
```
#### Builtins:
* `cd` (change directory)
* `exit` (exit program)
* `pwd` (print current working directory)
* `env` (prints environment variables)
* `setenv` (sets a new environment variable)
* `unsetenv` (unset a environment variable)

### Function and System Calls Utilized
 `access`, `chdir`, `close`, `execve`, `exit`, `fork`, `free`,
`fstat`, `getcwd`, `getline`, `malloc`,`perror`, `read`,  `wait`

## Notes
This shell does not handle comments, logical operators, alias, and variables.

## Known Bugs
Currently cannot remove the first environment variable with unsetenv.

### Authors
*Lisa Leung* - [Github](https://github.com/lisale0) || [Twitter](https://twitter.com/lisale01) || [email](lisa.leung@holbertonschool.com)

*Joe McDaniel* - [Github](https://github.com/joseph-mcdaniel) || [Twitter](https://twitter.com/joe_w_mcdaniel) || [email](joseph.mcdaniel@holbertonschool.com)
