#include "shell.h"

/**
 * _strcat - copy src to dest
 * @dest: the destination of the copy
 * @src: the source of the copy
 *
 * Return: char array and pointer
 */
char *_strcat(char *dest, const char *src)
{
	int dest_length, i, j;

	dest_length = _strlen(dest);

	for (i = dest_length, j = 0; src[j] != '\0'; i++, j++)
	{
		dest[i] = src[j];
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * _strlen - count the length of a string
 *  @s: char pointer
 *
 * Return: integer
 */
int _strlen(const char *s)
{
	int i, count;

	count = 0;
	for (i = 0; s[i] != '\0'; i++)
	{
		count++;
	}
	return (i);}
/**
 * _strdup - malloc, duplicate string
 * @str: the string to duplicate
 *
 * Return: char array
 */
char *_strdup(char *str)
{
	int i;
	char *ptr;

	if (str == NULL)
	{
		return (NULL);
	}
	ptr = malloc((_strlen(str) * sizeof(char)) + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	for (i = 0; str[i] != '\0'; i++)
	{
		*(ptr + i) = *(str + i);
	}
	ptr[i] = '\0';
	return (ptr);
}
/**
 * _strcpy - copies char array from src to dest
 * @dest: copying to
 * @src: copying from
 *
 * Return: char array dest
 */
char *_strcpy(char *dest, char *src)
{
	int length, i;

	length = _strlen((char *)src);
	if (dest == NULL)
		return NULL;
	for (i = 0; i < length; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';
	return (dest);
}
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
