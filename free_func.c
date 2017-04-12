#include "shell.h"

void freeenvlist(env_t **envlist)
{
	env_t *temp;

        while (*envlist != NULL)
	{
		temp = *envlist;
		*envlist = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
	free(*envlist);
}

void free_dblechar(char **arr)
{
	int i = 0;
	while(arr[i] != NULL)
	{
	       	printf("dblechar: %s\n", arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
}

void freearg(char **arg)
{
	free(arg);
}
