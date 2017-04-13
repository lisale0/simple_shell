#ifndef SHELL_H
#define SHELL_H
/**
 * all libraries below are included in all the c files for this project
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

/**
 *
 */
#define BUFSIZE 1024
#define TOKSIZE 64
#define DELIM " \t\n"
extern char **environ;
/**
 * struct env - data structure, linked list for environ
 * @key: the key of the environment variable
 * @value: the values of the environment variable
 *
 * Description: a linked list for environment variables
 */
typedef struct env
{
        char *key;
        char *value;
	int count;
        struct env *next;
}env_t;


typedef struct structlist
{
	env_t *envlist;
}structlist_t;

/**
 * struct - structure for commands and functions
 * @cmd: the input command by user
 * @f: function pointer
 */

typedef struct cmds
{
	char *cmd;
	int (*f)();
}cmds_t;
/**
 * struct - structure for builtins
 * @builtins: user input
 * @f: function pointer
 */
typedef struct builtins
{
	char *builtin;
	int (*f)();
}bt_t;
/**
 * primary functions in main file
 */
void set_envlist(env_t **envlist);
void prompt_user(env_t **envlist);
char **split_line(char *line);
int execute_arg(env_t **envlist, char **arg);

/**
 * get, set, and unset env
 */
char *_getenv(env_t *envlist, const char *name);
int _setenv(env_t **envlist, const char *name, const char *value);
int _unsetenv(env_t **envlist, const char *name);

/**
 * string helper functions
 */
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);

/**
 * functions for environ data structure
 */
size_t print_listenv(env_t *envlist);
void add_nodeenv_end(env_t **envlist, char *env);

/**
 * cd
 */
int exec_exit(env_t **envlist, char *cmd, char **arg);
int exec_cd(env_t **envlist, char *cmd, char **arg);
int exec_env(env_t **envlist,
	      __attribute__((unused))char *cmd, __attribute__((unused))char **arg);
int exec_setenv(env_t **envlist, char *cmd, char **arg);

/**
 * free functions
 */
void freeenvlist(env_t **envlist);
void freearg(char **arg);
void free_dblchar(char **arr);

/**
 * path functions
 */

char **parse_path(env_t *envlist);
char *build_path(char *cmd, char **parsedpaths);
/**
 * other functions
 */
char **envl_to_dptr(env_t **envlist);
char *_getline();
void printtest();
#endif
