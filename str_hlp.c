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

/**
 * _strcmp - compares string
 * @s1: first string
 * @s2: second string
 *
 * Return: Int
 */
int _strcmp(char *s1, char *s2)
{
	int i, dif, s1_length;

	dif = 0;
	s1_length = _strlen(s1);
	for (i = 0; i < s1_length; i++)
	{
		if ((int)s1[i] != (int)s2[i])
		{
			dif = -1;
			break;
		}
	}
	return (dif);
}
