#include "shell.h"

char **parse_path(env_t *envlist)
{
	char **patharr;
	char *path;
	char *tokpath;
	char *delim = ":";
	int i = 0, size = TOKSIZE;

	path = _getenv(envlist, "PATH");
	printf("env: %p\n", _getenv(envlist, "PATH"));
	printf("path: %p\n", path);

	patharr = malloc(sizeof(char *) * size);
	if (patharr == NULL)
		return (NULL);

	tokpath = strtok(path, delim);
	while (tokpath != NULL)
	{
		patharr[i] = strdup(tokpath);
		printf("patharr[%d]: %s", i, patharr[i]);
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

char *build_path(char *cmd, char **parsedpaths)
{
	char *pathname;
	int i = 0, len = 0, cmdlen, pathlen;

	cmdlen = _strlen(cmd);
	printf("cmdlen %d\n", cmdlen);

	while(parsedpaths[i] != NULL)
	{
		/*
		pathlen = _strlen(parsedpaths[i]);
		pathname = malloc(pathlen + cmdlen + 2);
		pathname = strcpy(pathname, parsedpaths[i]);
		pathname = strcat(pathname, "/");
		pathname = strcat(pathname, cmd);
		pathname = strcat(pathname, "\0");
		printf("%s", pathname);
		if (access(pathname, F_OK) == 0)
		{
			printf("pathname found: %s\n", pathname);
			return(pathname);
		}
		*/
		i++;
	}
	return (NULL);
}
