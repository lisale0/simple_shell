#ifndef SHELL_H
#define SHELL_H
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
#define BUFSIZE 1024
#define DELIM " \t\n"

/**
 * env - data structure, linked list for environ
 *
 */
typedef struct env
{
        char *key;
        char *value;
        struct env *next;
}env_t;
/**global*/

typedef struct alias
{
        char *key;
        char *value;
        struct alias *next;
}alias_t;

typedef struct structlist
{
	env_t *envlist;
}structlist_t;

/**
 * primary functions in main file
 */
void set_envlist(env_t **envlist);
void prompt_user();
char **split_line(char *line);
int execute_arg(char **arg);

/**
 * get, set, and unset env
 */
char *_getenv(const structlist_t *structlist, const char *name);
int _setenv(structlist_t **structlist, const char *name, const char *value);
int _unsetenv(const char *name);

/**
 * string helper functions
 */
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);

/**
 * functions for environ data structure
 */
size_t print_listenv(const structlist_t *structlist);
void add_nodeenv_end(structlist_t **structlist, char *env);

char *_getline();
void printtest();
#endif
