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

/**
 * struct structlist - struct containing pointers to other structs
 * @envlist: linked list of the environment variables
 *
 * Description: packages all other structs into one struct for referencing
 */
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
	void (*f)();
}cmds_t;
/**
 * primary functions in main file
 */
void set_envlist(env_t **envlist);
void prompt_user(structlist_t **structlist);
char **split_line(char *line);
int execute_arg(structlist_t **structlist, char **arg);

/**
 * get, set, and unset env
 */
char *_getenv(const structlist_t *structlist, const char *name);
int _setenv(structlist_t **structlist, const char *name, const char *value);
int _unsetenv(structlist_t **structlist, const char *name);

/**
 * string helper functions
 */
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);

/**
 * functions for environ data structure
 */
size_t print_listenv(structlist_t *structlist);
void add_nodeenv_end(structlist_t **structlist, char *env);

/**
 * cd
 */

void exec_cd(structlist_t **structlist, char *cmd, char **arg);
void exec_env(structlist_t **structlist,
	      __attribute__((unused))char *cmd, __attribute__((unused))char **arg);
void exec_setenv(structlist_t **structlist, char *cmd, char **arg);
/**
 * other functions
 */
char *_getline();
void printtest();
#endif
