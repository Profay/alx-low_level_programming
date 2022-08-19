#include "lists.h"
#include <stdio.h>

/**
 * print_listint - Print elements of a singly linked list.
 * @h: Pointer to a list.
 * Return: Unsigned Integer.
 **/

size_t print_listint(const listint_t *h)
{
	const listint_t *temp;
	unsigned int cntr = 0;

	temp = h;
	while (temp)
	{
		printf("%d\n", temp->n);
		cntr++;
		temp = temp->next;
	}
	return (cntr);
}
