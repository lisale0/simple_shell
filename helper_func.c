#include "shell.h"

/**
 * _realloc - reallocating memory from previous pointer to new mem
 * @ptr: where ptr is a pointer to the memory previously allocated
 * with a call to malloc
 * @old_size: old size
 * @new_size: new size
 *
 * Return: reallocated pointer with new size
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;
	char *newptrcpy, *ptrcpy;
	unsigned int i;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (new_size == old_size)
		return (ptr);
	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);
	if (ptr == NULL)
		return (newptr);

	ptrcpy = ptr;
	newptrcpy = newptr;
	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			newptrcpy[i] = ptrcpy[i];
	}
	else
	{
		for (i = 0; i < new_size; i++)
			newptrcpy[i] = ptrcpy[i];
	}
	free(ptr);
	return (newptr);
}

/**
 * set_pathvar - setting the variable path for current and old pwd
 * @envlist: env list to be manipulated
 * @oldpath: the oldpath
 * @currentpath: the current path
 *
 * Return: none
 */
void set_pathvar(env_t **envlist, char *oldpath,
		 __attribute__((unused))char *currentpath)
{
	env_t *temp;
	int oldlen, newlen;

	temp = *envlist;
	while (temp != NULL)
	{
		if (_strcmp(temp->key, "PWD") == 0)
		{
			oldlen = _strlen(temp->value) + 1;
			newlen = _strlen(oldpath) + 1;
			temp->value = _realloc(temp->value, oldlen, newlen);
			_strcpy(temp->value, oldpath);
		}
		if (_strcmp(temp->key, "OLDPWD") == 0)
		{
			oldlen = _strlen(temp->value) + 1;
                        newlen = _strlen(oldpath) + 1;
			_realloc(temp->value, oldlen, newlen);
			_strcpy(temp->value, currentpath);
		}
		temp = temp->next;
	}
}
