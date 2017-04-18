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

	/*new size 0 and ptr not NULL*/
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	/*new_size same as old_size, no need to reallocate new mem*/
	if (new_size == old_size)
		return (ptr);
	/*always allocate memory of new size*/
	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);
	/*If ptr is NULL, then the call is equivalent to malloc(new_size),*/
	/*  for all values of old_size and new_size*/
	if (ptr == NULL)
		return (newptr);

	ptrcpy = ptr;
	newptrcpy = newptr;
	/*if the newsize if bigger than the old_size, just keep old size*/
	if (new_size > old_size)
	{
		for (i = 0; i < old_size; i++)
			newptrcpy[i] = ptrcpy[i];
	}
	/*if the old size id bigger make sure to get the new size, more mem*/
	else
	{
		for (i = 0; i < new_size; i++)
			newptrcpy[i] = ptrcpy[i];
	}
	/*free ptr*/
	free(ptr);
	return (newptr);
}

void set_pathvar(env_t **envlist, char *oldpath, __attribute__((unused))char *currentpath)
{

	env_t *temp;
	int oldlen, newlen;

	temp = *envlist;
	while (temp != NULL)
	{
		if (_strcmp(temp->key, "PWD") == 0)
		{
			printf("found %s\n", temp->key);
			printf("value before change: %s\n", temp->value);
			printf("value to change to: %s\n", oldpath);
			oldlen = _strlen(temp->value) + 1;
			newlen = _strlen(oldpath) + 1;
			printf("oldlen: %d newlen %d\n", oldlen, newlen);


			temp->value = _realloc(temp->value, oldlen, newlen);
/*
			printf("%d\n", _strlen(temp->value));

			_strcpy(temp->value, oldpath);


			printf("value after change: %s\n", temp->value);
*/
		}
		/*
		if (_strcmp(temp->key, "OLDPWD") == 0)
		{
			printf("found %s\n", temp->key);
			printf("value before change: %s\n", temp->value);
			oldlen = _strlen(temp->value) + 1;
                        newlen = _strlen(oldpath) + 1;
			_realloc(temp->value, oldlen, newlen);
			_strcpy(temp->value, currentpath);
			printf("value after change: %s\n", temp->value);
		}
		*/
		temp = temp->next;
	}
}
