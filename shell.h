#ifndef SHELL_H
#define SHELL_H

/**libraries**/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

/**Macros**/
#define BUFSIZE 1024
#define TOKSIZE 64
#define DELIM "\t\n\r\" "
#define PS1 "$ "
#define SUCCESS 1
#define FAIL -1

/**Global**/
extern char **environ;

/**structs**/
/**
 * struct env - data structure, linked list for environ
 * @key: the key of the environment variable
 * @value: the values of the environment variable
 * @count: the count of the linkedlist
 * @next: pointer to the next node
 *
 * Description: a linked list for environment variables
 */
typedef struct env
{
	char *key;
	char *value;
	int count;
	struct env *next;
} env_t;

/**
 * struct builtins- structure for builtins
 * @builtin: user input
 * @f: function pointer
 *
 * Description: builtin structure
 */
typedef struct builtins
{
	char *builtin;
	int (*f)();
} bt_t;

/** primary functions in main file [sh-main.c]**/
void set_envlist(env_t **envlist);
void prompt_user(env_t **envlist, char **patharr, int pipe);
char **split_line(char *line);
int execute_cmd(env_t **envlist, char ***arg, char **patharr, int pipe);
void write_prompt();
/**
 * execute_arg - primary function that calls execve
 * @envlist: the linked list used to grab values
 * @arg: the arguments, contains command and flag
 * @path: either the passed in path or built out one
 *
 * Return: 0 if it does not fail
 */
int execute_arg(__attribute__((unused))env_t **envlist,
		char **arg, char *path);
int check_builtin(char ***arg, env_t **envlist);

/**get, set, and unset env, manipulation of nodes in the link [env_cmd.c]**/
env_t *_getenv(env_t *envlist, char *name);
int _setenv(env_t **envlist, char *name, char *value);
int _unsetenv(env_t **envlist, char *name);

/**functions for env_t envlist [env_list.c] add node, print the list**/
size_t print_listenv(env_t *envlist);
void add_nodeenv_end(env_t **envlist, char *env);
char *concat_env(char *key, char *value, int *len);

/**function pointers in C points to these functions [builtin.c] builtins**/
int exec_cd(env_t **envlist, char *cmd, char **arg);
/**
 * exec_env - executes the builtin env
 * @envlist: the linked list used to grab values
 * @cmd: the command
 * @arg: the arguments
 *
 * Return: 0 if it does not fail
 */
int exec_env(__attribute__((unused)) env_t **envlist,
__attribute__((unused)) char *cmd, __attribute__((unused)) char **arg);
int exec_setenv(env_t **envlist, char *cmd, char **arg);
/**
 * exec_unsetenv - executes the builtin unsetenv
 * @envlist: the linked list used to grab values
 * @cmd: the command
 * @arg: the arguments
 *
 * Return: 0 if it does not fail
 */
int exec_unsetenv(env_t **envlist, __attribute__((unused))char *cmd,
		  char **arg);

/**free functions [free_func.c]**/
void freeenvlist(env_t **envlist);
void freearg(char **arg);
void free_dblechar(char **arr);

/**path functions [path.c]**/
char **parse_path(env_t *envlist);
int build_path(char *cmd, char **parsedpaths, char **path);

/**string helper functions [str_hlp.c]**/
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void set_pathvar(env_t **envlist, char *oldpath, char *currentpath);
char **envl_to_dptr(env_t **envlist);
int arr_size(char **arr);
int check_exit(char *cmd, char ***arg, char **line);
int check_space(int cmd);
void set_homepath(env_t **envlist, char *oldpath);

/**
 * build_cdpaths - builts out the paths for cd
 * @envlist: the linked list used to grab values
 * @temp: used to store old pwd
 * @temp2: used to store pwd
 * @oldpath: old path is reset based on temp
 * @currentpath: currentpath is set based on cwd
 * @cwdlen: used to keep track of length of cwd, to be used in exec_cd
 *
 * Return: 0 if it does not fail
 */
int build_cdpaths(env_t **envlist, env_t **temp, env_t **temp2,
		  char **oldpath, char **currentpath, size_t *cwdlen);
#endif
