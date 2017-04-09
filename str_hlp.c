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
	return (i);
}
