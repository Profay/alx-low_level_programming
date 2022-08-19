#include "hash_tables.h"
/**
 * hash_table_print - prints a hash table
 * @ht: hash table
 * Return: None
 */
void hash_table_print(const hash_table_t *ht)
{
	unsigned long int index;
	unsigned long int i = 0;
	hash_node_t *temp;

	if (ht == NULL)
		return;
	printf("{");
	for (index = 0; index < ht->size; index++)
	{
		temp = ht->array[index];
		while (temp)
		{
			if (i > 0)
				printf(", ");
			printf("'%s: %s'", temp->key, temp->value);
			i++;
			temp = temp->next;
		}
	}
	printf("}\n");
}
