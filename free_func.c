#include "shell.h"

void freeenvlist(structlist_t **structlist)
{
	env_t *temp;

        while ((*structlist)->envlist != NULL)
	{
		temp = (*structlist)->envlist;
		(*structlist)->envlist = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void freearg(char ***arg)
{
	int i = 0;
	while(*arg != NULL)
	{
		free(arg[i][0]);
		i++;
	}
	free(arg[0]);
}
