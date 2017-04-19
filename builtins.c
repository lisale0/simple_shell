#include "shell.h"
#include <stdio.h>

/**
 * exec_cd - called by function pointer
 * executes the builtin cd
 * @envlist: the linkedlist of environment variables
 * @cmd: command
 * @arg: the arguments for cd
 *
 * Return: 1 success, 0 fail
 */
int exec_cd(__attribute__((unused))env_t **envlist,
	    __attribute__((unused))char *cmd, char **arg)
{
	env_t *temp, *temp2, *home;
	char *oldpath, *currentpath;
	size_t cwdlen = 0;

	build_cdpaths(envlist, &temp, &temp2, &oldpath, &currentpath, &cwdlen);
	if (arg[1] == NULL)
	{
		home = _getenv(*envlist, "HOME");
		chdir(home->value);
	}
	else
	{
		if (_strcmp(arg[1], "-") == 0)
		{
			if ((chdir(oldpath)) == 0)
			{
				set_pathvar(envlist, oldpath, currentpath);
			}

		}
	}
	free(oldpath);
	free(currentpath);
	return (1);
}

/**
 * exec_env - called by function pointer
 * executes the builtin env
 * @envlist: the linkedlist of environment variables
 * @cmd: command
 * @arg: the arguments for cd
 *
 * Return: 1 success, 0 fail
 */
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

/**
 * exec_setenv - called by function pointer
 * executes the builtin setenv
 * @envlist: the linkedlist of environment variables
 * @cmd: command
 * @arg: the arguments for cd
 *
 * Return: 1 success, 0 fail
 */
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
	_setenv(envlist, name, value);
	free(name);
	free(value);
	return (0);
}

/**
 * exec_unsetenv - called by function pointer
 * executes the builtin unsetenv
 * @envlist: the linkedlist of environment variables
 * @cmd: command
 * @arg: the arguments for cd
 *
 * Return: 1 success, 0 fail
 */
int exec_unsetenv(env_t **envlist,
		  __attribute__((unused)) char *cmd, char **arg)
{
	if (arg[1] == NULL)
	{
		perror("invalid arg");
		return (-1);
	}
	_unsetenv(envlist, arg[1]);
	return (0);
}
