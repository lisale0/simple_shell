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
typedef struct alias
{
        char *key;
        char *value;
        struct alias *next;
}alias_t;

/**
 * primary functions in main file
 */
void prompt_user();
char **split_line(char *line);
int execute_arg(char **arg);

/**
 * get, set, and unset env
 */
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);

/**
 * functions for environ data structure
 */
void add_nodeenv(env_t **envlist, char *env);
size_t print_listenv(const env_t *h);
void add_nodeenv_end(env_t **head, char *env);

char *_getline();

#endif
