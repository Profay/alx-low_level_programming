#include "search_algos.h"

/**
 * linear_search - searches for a value in an array of
 * integers using the Linear search algorithm
 *
 * @array: input array
 * @size: size of the array
 * @value: value to search in
 * Return: Always EXIT_SUCCESS
 */

int linear_search(int *array, size_t size, int value)
{
size_t index = 0;

for (index = 0; index < size; index++)
{
printf("Value checked array[%ld] = [%d]\n", index, array[index]);
if (array[index] == value)
{
return (index);
}
}
return (-1);
}
