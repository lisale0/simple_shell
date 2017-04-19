#ifndef SHELL_H
#define SHELL_H
/**
 * libraries
 */
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

/**
 * Macros
 */
#define BUFSIZE 1024
#define TOKSIZE 64
#define DELIM " \t\n\r\""

/**
 * Global
 */
extern char **environ;

/**
 * struct env - data structure, linked list for environ
 * @key: the key of the environment variable
 * @value: the values of the environment variable
 * @count: the count of the linkedlist
 * @next: pointer to the next node
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
 * struct - structure for builtins
 * @builtins: user input
 * @f: function pointer
 * Description: builtin commands
 */
typedef struct builtins
{
	char *builtin;
	int (*f)();
} bt_t;

/**
 * primary functions in main file [sh-main.c]
 */
void set_envlist(env_t **envlist);
void prompt_user(env_t **envlist, char **patharr);
char **split_line(char *line);
int execute_arg(env_t **envlist, char **arg, char *path);
int check_builtin(char ***arg, env_t **envlist);

/**
 * get, set, and unset env, manipulation of nodes in the link [env_cmd.c]
 */
env_t *_getenv(env_t *envlist, char *name);
int _setenv(env_t **envlist, char *name, char *value);
int _unsetenv(env_t **envlist, char *name);

/**
 * functions for env_t envlist [env_list.c]
 * add node, print the list
 */
size_t print_listenv(env_t *envlist);
void add_nodeenv_end(env_t **envlist, char *env);
char *concat_env(char *key, char *value, int *len);
/**
 * function pointers in C points to these functions [builtin.c]
 * execute builtins
 */
int exec_exit(env_t **envlist, char *cmd, char **arg);
int exec_cd(env_t **envlist, char *cmd, char **arg);
int exec_env(__attribute__((unused)) env_t **envlist,
__attribute__((unused)) char *cmd, __attribute__((unused)) char **arg);
int exec_setenv(env_t **envlist, char *cmd, char **arg);
int exec_unsetenv(env_t **envlist,
		  __attribute__((unused))char *cmd, char **arg);

/**
 * builtins 2
 */
int exec_nl(__attribute__((unused))env_t **envlist,
	    __attribute__((unused))char *cmd, char **arg);
/**
 * free functions [free_func.c]
 */
void freeenvlist(env_t **envlist);
void freearg(char **arg);
void free_dblechar(char **arr);

/**
 * path functions [path.c]
 */
char **parse_path(env_t *envlist);
int build_path(char *cmd, char **parsedpaths, char **path);
int check_cwdex(char *cmd);
/**
 * string helper functions [str_hlp.c]
 */
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);
char *_strdup(char *str);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);

/**
 * getline.c
 */
int _getline(char **lineptr, size_t *a);

/**
 * signal.c
 */
/**
 * other functions
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void set_pathvar(env_t **envlist, char *oldpath, char *currentpath);
char **envl_to_dptr(env_t **envlist);
int arr_size(char **arr);
int check_exit(char *cmd, char ***arg, char **line);
int check_space(int cmd);
int execute_cmd(env_t **envlist, char **arg, char *cmd, char **patharr);
#endif
