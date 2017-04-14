#include "shell.h"
#include <stdio.h>

int exec_cd(__attribute__((unused))env_t **envlist, __attribute__((unused))char *cmd, char **arg)
{
	env_t *temp, *temp2;
	char *oldpath, *currentpath;

        if (arg[1] == NULL)
                fprintf(stderr, "SH: expected argument.\n");
        else
        {
		if (_strcmp(arg[1], "-") == 0)
		{
			printf("hello\n");
			temp = _getenv(*envlist, "OLDPWD");
			oldpath = malloc((_strlen(temp->value) + 1)
					 * sizeof(char));
			if (oldpath == NULL)
				return (-1);
			temp2 = _getenv(*envlist, "PWD");
			currentpath = malloc((_strlen(temp2->value) + 1)
					     * sizeof(char));
			if (currentpath == NULL)
			{
				free(oldpath);
				return (-1);
			}
			oldpath = strcpy(oldpath, temp->value);
			printf("%s\n", oldpath);
			chdir(oldpath);
			return (1);
		}
                if (chdir(arg[1]) != 0)
                        perror("sh");
        }
        return (1);
}
int exec_exit(__attribute__((unused)) env_t **envlist, __attribute__((unused)) char *cmd, __attribute__((unused)) char **arg)
{
	return (0);
}
int exec_env(env_t **envlist,
__attribute__((unused)) char *cmd, __attribute__((unused)) char **arg)
{
	if (envlist == NULL)
	{
		perror("hsh environment list is NULL");
		return (0);
	}
	print_listenv(*envlist);
	return (1);
}
int exec_setenv(env_t **envlist, __attribute__((unused)) char *cmd, char **arg)
{
	char *name, *value;
	int namelen, valuelen;

	if (arg[1] == NULL || arg[2] == NULL)
	{
		perror("hsh: insufficient argument");
		return (-1);
	}
	namelen = _strlen(arg[1]);
	valuelen = _strlen(arg[2]);
	name = malloc(namelen * sizeof(char));
	if (name == NULL)
		return (-1);
	value = malloc((valuelen + 1) * sizeof(char));
	if (value == NULL)
		return (-1);
	strcpy(name, arg[1]);
	strcpy(value, arg[2]);
	strcat(value, "\0");
	_setenv(envlist,name, value);
	free(name);
	free(value);
	return (0);
}
int exec_unsetenv(env_t **envlist, __attribute__((unused)) char *cmd, char **arg)
{
	if (arg[1] == NULL)
	{
		perror("invalid arg");
		return (-1);
	}
	_unsetenv(envlist, arg[1]);
	return (0);
}
