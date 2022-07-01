#include "hash_tables.h"
/**
 * hash_table_delete - delete a hash table
 * @ht: hash table
 * Return: None
 */
void hash_table_delete(hash_table_t *ht)
{
	hash_node_t *temp;
	hash_node_t *head;
	unsigned long int index;

	if (ht == NULL)
		return;
	for (index = 0; index < ht->size; index++)
	{
		head = ht->array[index];
		while (head != NULL)
		{
			temp = head->next;
			free(head->key);
			free(head->value);
			free(head);
			head = temp;
		}
	}
	free(ht->array);
	free(ht);
}
