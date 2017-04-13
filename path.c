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
	int i = 0, size = TOKSIZE;

	path = _getenv(envlist, "PATH");
	patharr = malloc(sizeof(char *) * size);
	if (patharr == NULL)
		return (NULL);

	tokpath = strtok(path, delim);
	while (tokpath != NULL)
	{
		patharr[i] = strdup(tokpath);
		i++;
		if (i >= size)
		{
			size += TOKSIZE;
			patharr = realloc(patharr, sizeof(char *) * size);
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
 *
 * Return: string path
 */
char *build_path(char *cmd, char **parsedpaths)
{
	char *pathname;
	int i = 0, cmdlen, pathlen, mem;

	cmdlen = _strlen(cmd);
	while (parsedpaths[i] != NULL)
	{
		pathlen = _strlen(parsedpaths[i]);
		mem = pathlen + cmdlen + 2;
		pathname = malloc(mem * sizeof(char));
		if (pathname == NULL)
			return (NULL);
		pathname = strcpy(pathname, parsedpaths[i]);
		pathname = strcat(pathname, "/");
		pathname = strcat(pathname, cmd);
		pathname = strcat(pathname, "\0");
		if (access(pathname, F_OK) == 0)
		{
			return (pathname);
		}
		free(pathname);
		i++;
	}
	return (NULL);
}
