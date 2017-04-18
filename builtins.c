#include "shell.h"
#include <stdio.h>

int exec_cd(__attribute__((unused))env_t **envlist, __attribute__((unused))char *cmd, char **arg)
{
	env_t *temp, *temp2;
	char *oldpath;
	char currentpath[1024];

	size_t cwdlen = 0;

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
			cwdlen = (size_t)_strlen(temp2->value);

			/*printf("PWD %s\n", temp2->value);*/
			/*
			currentpath = malloc((cwdlen + 1)
					     * sizeof(char));
			if (currentpath == NULL)
			{
				free(oldpath);
				return (-1);
			}
			*/
			/*getting the old path so I can change to that*/
			oldpath = strcpy(oldpath, temp->value);
	        	if (getcwd(currentpath, cwdlen) != NULL)
			{
                                printf("Current working dir: %s\n", currentpath);
				return (-1);;
			}
			if ((chdir(oldpath)) == 0)
			{
				/*oldpath = _realloc(oldpath, _strlen(oldpath));*/
				/*PWD is not oldpath*/
				_strcpy(temp2->value, oldpath);
				/*change OLDPWD to currentpath*/
				_strcpy(temp->value, currentpath);
			}
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
	name = malloc((namelen + 2) * sizeof(char));
	if (name == NULL)
		return (-1);
	value = malloc((valuelen + 2) * sizeof(char));
	if (value == NULL)
		return (-1);
	_strcpy(name, arg[1]);
	_strcpy(value, arg[2]);
	_strcat(value, "\0");
	_strcat(name, "\0");
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
