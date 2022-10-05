#include <stdio.h>
#include <stdlib.h>
#include "search_algos.h"
/**
 * binary_search - search for a value in a sorted array of integers
 * @array: a pointer to the first element of the array to search in
 * @size: the number of elements in array
 * @value: the value to search for
 * Return: if array is NULL, your function must return -1
 */

int binary_search(int *array, size_t size, int value)
{
	int min = 0;
	int max = size - 1;
	int mid;
	int i;

	if (array == NULL || size == 0)
		return (-1);

	while (min <= max)
	{
		printf("Searching in array: ");
		for (i = min; i <= max; i++)
		{
			if (i == max)
				printf("%d\n", array[i]);
			else
				printf("%d, ", array[i]);
		}
		mid = min + (max - min) / 2;
		if (value == array[mid])
			return (mid);
		if (value > array[mid])
			min = mid + 1;
		else
			max = mid - 1;
	}
	return (-1);
}
