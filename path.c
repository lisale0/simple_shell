#include "shell.h"

/**
 * parse_path - parsing path from linkedlist envlist
 * @envlist: linkedlist envlist
 *
 * Return: double dimensional array
 */
char **parse_path(env_t *envlist)
{
	char **patharr;
	char *path;
	char *tokpath;
	char *delim = ":";
	int i = 0, size = TOKSIZE, oldsize;
	env_t *node;

	node = _getenv(envlist, "PATH");
	path = node->value;
	patharr = malloc(sizeof(char *) * size);
	if (patharr == NULL)
		return (NULL);

	tokpath = strtok(path, delim);
	while (tokpath != NULL)
	{
		patharr[i] = _strdup(tokpath);
		i++;
		if (i >= size)
		{
			oldsize = size;
			size += TOKSIZE;
			patharr = _realloc(patharr, oldsize, sizeof(char *) * size);
			if (patharr == NULL)
				perror("tokenize fail");
		}
		tokpath = strtok(NULL, delim);
	}
	patharr[i] = NULL;
	return (patharr);
}

/**
 * build_path - find path where command is an executable
 * @cmd: command
 * @parsedpaths: all the different paths
 * @path: the path gets returns to main
 * Return: string path
 */
int build_path(char *cmd, char **parsedpaths, char **path)
{
	char *pathname = "";
	int i = 0, cmdlen, pathlen, mem;

	cmdlen = _strlen(cmd);
	while (parsedpaths[i] != NULL)
	{
		pathlen = _strlen(parsedpaths[i]);
		mem = pathlen + cmdlen + 2;
		pathname = malloc(mem * sizeof(char));
		if (pathname == NULL)
			return (0);
		pathname = _strcpy(pathname, parsedpaths[i]);
		pathname = _strcat(pathname, "/");
		pathname = _strcat(pathname, cmd);
		pathname = _strcat(pathname, "\0");
		if (access(pathname, X_OK) == 0)
		{
			*path = pathname;
			return (1);
		}
		free(pathname);
		i++;
	}
	return (0);
}
