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

void freeptrenv(char **envlist)
{
	int i = 0;
	while(envlist[i] != NULL)
	{
		free(envlist[i]);
	}
	free(envlist);
}

void freearg(char **arg)
{
	free(arg);
}
