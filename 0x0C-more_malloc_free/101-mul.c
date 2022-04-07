#include "main.h"
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * _isdigit - check if a char is a digit
 * @c: char to be checked
 *
 * Return: 1 if digit, 0 othewise
 */
int _isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

/**
 * print_string - prints a null terminated string
 * @s: pointer to string
 *
 * Return: void
 */
void print_string(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		_putchar(s[i]);
	_putchar('\n');
}

/**
 * str_concat - concats two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: pointer to the new string
 */
char *str_concat(char *s1, char *s2)
{
	int i, size1, size2;
	char *arr;

	if (s1 == NULL)
	s1 = "";
	if (s2 == NULL)
	s2 = "";

	size1 = 0;
	size2 = 0;
	i = 0;
	while (s1[i])
	{
		size1++;
		i++;
	}
	i = 0;
	while (s2[i])
	{
		size2++;
		i++;
	}

	arr = malloc(sizeof(char) * (size1 + size2 + 1));
	if (arr == NULL)
		return (NULL);

	for (i = 0; i < size1; i++)
		arr[i] = s1[i];
	for (; i < size1 + size2; i++)
		arr[i] = *s2++;
	arr[i] = '\0';
	return (arr);
}

/**
 * add - adds two numbers in strings
 * @sum: the sum
 * @n1: n1
 * @n2: n2
 * @i: i
 * @j: j
 * @k: k
 * @size_r: size_r
 *
 * Return: sum if successful, 0 if not
 */
char *add(char *sum, char *n1, char *n2, int i, int j, int k, int size_r)
{
	int a, b, c, d;

	k = size_r - 1;
	d = 0;
	while (i >= -1 || j >= -1)
	{
		if (k < 0)
			return (NULL);
		if (i < 0)
			a = 0;
		else
			a = n1[i] - '0';
		if (j < 0)
			b = 0;
		else
			b = n2[j] - '0';
		c = (a + b + d) % 10;

		if (a + b + d < 10)
		{
			sum[k] = ((sum[k] - '0') + (a + b + d)) + '0';
			d = 0;
		}
		else
		{
			sum[k] = ((sum[k] - '0') + c) + '0';
			d = 1;
		}
		i--;
		j--;
		k--;
	}
	sum[size_r] = '\0';
	while (*sum - '0' == 0 && *(sum + 1) != '\0')
		sum++;
	return (sum);
}

/**
 * infinite_add - adds two strings containing numbers
 * @n1: the first number
 * @n2: the second number
 *
 * Return: pointer to the sum
 */
char *infinite_add(char *n1, char *n2)
{
	char *sum;
	int i, j, k, size1, size2, size_r;

	size1 = 0;
	size2 = 0;
	for (i = 0; n1[i] != '\0'; i++)
		size1++;
	for (i = 0; n2[i] != '\0'; i++)
		size2++;
	size_r = ((size1 > size2) ? size1 : size2) + 1;
	sum = malloc(sizeof(char) * (size_r + 1));
	if (sum == NULL)
		return (NULL);
	i = size1 - 1;
	j = size2 - 1;
	for (k = 0; k < size_r; k++)
		sum[k] = 0 + '0';
	return (add(sum, n1, n2, i, j, k, size_r));
}

/**
 * mul - multiplies two positive numbers
 * @num1: first number
 * @num2: second number
 *
 * Return: the produt if successful, status of 98 if not
 */
char *mul(char *num1, char *num2)
{
	int i, j, size1, size2;
	char *product, *power;
	char **acc;

	size1 = 0;
	size2 = 0;
	for (i = 0; num1[i] != '\0'; i++)
		size1++;
	for (i = 0; num2[i] != '\0'; i++)
		size2++;
	acc = (char **)malloc(sizeof(char) * size2);
	if (acc == NULL)
		return (NULL);
	for (i = 0; i < size2; i++)
	{
		acc[i] = (char *)malloc(sizeof(char) * (size1 + size2 + 2));
		if (acc[i] == NULL)
		{
			for (j = 0; j < i; j++)
				free(acc[j]);
			return (NULL);
		}
	}

	power = "";
	for (i = size2 - 1; i >= 0; i--)
	{
		acc[i] = "0";
		for (j = 0; j < (num2[i] - '0'); j++)
			acc[i] = infinite_add(acc[i], num1);
		acc[i] = str_concat(acc[i], power);
		power = str_concat(power, "0");

	}
	product = "";
	for (i = 0; i < size2; i++)
		product = infinite_add(product, acc[i]);
	return (product);
}

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 if successful, status of 98 if not
 */
int main(int argc, char *argv[])
{
	int i, j;
	char *product;
	char *error = "Error";

	if (argc != 3)
	{
		print_string(error);
		exit(98);
	}
	for (i = 1; i < argc; i++)
		for (j = 0; argv[i][j] != '\0'; j++)
			if (!_isdigit(argv[i][j]))
			{
				print_string(error);
				exit(98);
			}
	product = mul(argv[1], argv[2]);
	if (product == NULL)
		return (1);
	print_string(product);
	return (0);
}
