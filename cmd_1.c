#include "shell.h"
#include <stdio.h>
void exec_cd(structlist_t **structlist, char *cmd, char **arg)
{
	chdir(arg[1]);
}
void exec_env(structlist_t **structlist,
__attribute__((unused))char *cmd, __attribute__((unused))char **arg)
{
	print_listenv(*structlist);
}
void exec_setenv(structlist_t **structlist, char *cmd, char **arg)
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
	_setenv(structlist,name, value);
	/*
	name = strtok(*arg, " ");
	value = strtok(NULL, "");
	_setenv(structlist, name, value);
	*/
}
