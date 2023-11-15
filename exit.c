#include "shell.h"

/**
 **shell_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *shell_strncpy(char *dest, char *src, int n)
{
	int k, y;
	char *s = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		y = k;
		while (y < n)
		{
			dest[y] = '\0';
			y++;
		}
	}
	return (s);
}

/**
 **shell_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *shell_strncat(char *dest, char *src, int n)
{
	int k, y;
	char *s = dest;

	k = 0;
	y = 0;
	while (dest[k] != '\0')
		k++;
	while (src[y] != '\0' && y < n)
	{
		dest[k] = src[y];
		k++;
		y++;
	}
	if (y < n)
		dest[k] = '\0';
	return (s);
}

/**
 **shell_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *shell_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

