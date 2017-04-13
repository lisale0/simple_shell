#include "shell.h"
#include <stdio.h>

int exec_cd(env_t **envlist, char *cmd, char **arg)
{
        if (arg[1] == NULL)
        {
                fprintf(stderr, "SH: expected argument.\n");
        }
        else
        {
                if (chdir(arg[1]) == 0)
                        perror("sh");
        }
        return (1);
}
int exec_exit(env_t **envlist, char *cmd, char **arg)
{
	return (0);
}
int exec_env(env_t **envlist,
__attribute__((unused))char *cmd, __attribute__((unused))char **arg)
{
	if (envlist == NULL)
	{
		perror("hsh environment list is NULL");
		return (0);
	}
	print_listenv(*envlist);
	return (1);
}
int exec_setenv(env_t **envlist, char *cmd, char **arg)
{
	char *name, *value;
	int namelen, valuelen;

	if (arg[1] == NULL || arg[2] == NULL)
	{
		perror("hsh: insufficient argument");
		return;
	}
	namelen = _strlen(arg[1]);
	valuelen = _strlen(arg[2]);
	name = malloc(namelen * sizeof(char));
	value = malloc(valuelen * sizeof(char));

	strcpy(name, arg[1]);
	strcpy(value, arg[2]);
	printf("%s=%s", name, value);
	_setenv(envlist,name, value);

	return (0);
}
