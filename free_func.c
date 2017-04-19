#include "shell.h"

/**
 * freeenvlist - free linkedlist nodes of env_t
 * @envlist: the envlist passed in
 *
 * Return: none; void function
 */
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

/**
 * free_dblechar - function to free double char
 * @arr: the array to free
 *
 * Return: none; void
 */
void free_dblechar(char **arr)
{
	int i = 0;

	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

/**
 * arr_size - gets the size of an array
 * @arr: the array to check against
 *
 * Return: int, size of array
 */
int arr_size(char **arr)
{
	int i;

	if (arr == NULL || *arr == NULL)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
