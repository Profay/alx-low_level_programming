#include "lists.h"

/**
 * listint_len - Calculates the number of elements.
 * @h: Pointer to a list.
 * Return: unsigned Integer.
 **/

size_t listint_len(const listint_t *h)
{
	const listint_t *tp;
	unsigned int len = 0;

	tp = h;
	while (tp)
	{
		len++;
		tp = tp->next;
	}
	return (len);
}
