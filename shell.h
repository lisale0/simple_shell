#ifndef SHELL_H
#define SHELL_H
char *_getenv(const char *name);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
char *_getline();
typedef struct alias
{
	char *key;
	char *value;
	struct alias *next;
}alias_t;

/**
 * arg to string
 */

char *argstostr(int ac, char **av);
void string_copy(int ac, char **av, char *newstr);
int mem_alloc(int ac, char **av);
int _strlen(char *s);

#endif
