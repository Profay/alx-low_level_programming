#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_tables.h"

shash_node_t *add_node(shash_table_t *ht, const char *key, const char *value);

/**
 * shash_table_create - create a sorted hash table
 *
 * @size: size of the hash table
 *
 * Return: pointer to the new hash table, NULL if it fails
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *new_table;

	new_table = malloc(sizeof(shash_table_t));
	if (!new_table)
		return (NULL);
	new_table->array = calloc(size, sizeof(shash_node_t *));
	if (!(new_table->array))
	{
		free(new_table);
		return (NULL);
	}
	new_table->size = size;
	new_table->shead = new_table->stail = NULL;

	return (new_table);
}

/**
 * shash_table_set - add a new key/value pair to the hash table
 *
 * @ht: pointer to the hash table
 * @key: key to hash
 * @value: value associated with key
 *
 * Return: 1 if it suceeded, 0 if not
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	int index;
	shash_node_t *node;

	if (!key || strcmp(key, "") == 0 || !ht)
		return (0);
	index = key_index((unsigned char *) key, ht->size);

	node = ht->array[index];
	while (node)
	{
		if (strcmp(node->key, key) == 0)
		{
			free(node->value);
			node->value = strdup(value);
			return (1);
		}
		node = node->next;
	}
	node = add_node(ht, key, value);
	if (!node)
		return (0);

	node->next = ht->array[index];
	ht->array[index] = node;

	return (1);
}

/**
 * add_node - continuation function to shash_table_set
 *
 * @ht: the hash table
 * @key: key to add
 * @value: value associated with key
 *
 * Descriprtion: inserts node into the sorted linked list
 *
 * Return: the new node, NULL if it fails
 *
 */
shash_node_t *add_node(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *node, *current;

	node = malloc(sizeof(shash_node_t));
	if (node == NULL)
		return (0);

	node->key = strdup(key);
	node->value = strdup(value);
	if ((!node->key) || !(node->value))
	{
		free(node);
		return (0);
	}

	if (!(ht->shead))
	{
		ht->shead = ht->stail = node;
		node->sprev = node->snext = NULL;
		return (node);
	}
	current = ht->shead;
	while (current)
	{
		if (strcmp(node->key, current->key) < 0)
		{
			node->snext = current;
			node->sprev = current->sprev;
			if (current->sprev)
				current->sprev->snext = node;
			else
				ht->shead = node;
			current->sprev = node;
			return (node);
		}
		if (current->snext == NULL)
		{
			current->snext = node;
			node->sprev = current;
			node->snext = NULL;
			ht->stail = node;
			return (node);
		}
		current = current->snext;
	}

	return (0);
}

/**
 * shash_table_print - print the sorted hash table
 *
 * @ht: the hash table
 *
 * Description: print the sorted linked list
 *
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *current;
	int firstItemFound = 0;

	if (!ht)
		return;
	current = (shash_node_t *)ht->shead;
	printf("{");
	while (current)
	{
		if (firstItemFound)
			printf(", ");
		printf("'%s': '%s'", current->key, current->value);
		current = current->snext;
		firstItemFound = 1;
	}
	printf("}\n");
}

/**
 * shash_table_print_rev - print the sorted hash table in reverse
 *
 * @ht: the hash table
 *
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *current;
	int firstItemFound = 0;

	if (!ht || !(ht->stail))
		return;

	printf("{");
	current = ht->stail;
	while (current)
	{
		if (firstItemFound)
			printf(", ");
		printf("'%s': '%s'", current->key, current->value);
		current = current->sprev;
		firstItemFound = 1;
	}
	printf("}\n");
}
/**
 * shash_table_get - retrieves values associated with a key
 *
 * @ht: the hash table
 * @key: the key to look for
 *
 * Return: value or NULL if key couldn't be found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *current;
	unsigned long int index;

	if (!ht || !key)
		return (NULL);
	index = key_index((unsigned char *)key, ht->size);
	current = ht->array[index];
	while (current)
	{
		if (strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}

	return (NULL);
}


/**
 * shash_table_delete - delete the sorted hash table
 *
 * @ht: the hash table
 *
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *current, *temp;

	if (!ht)
		return;

	current = ht->shead;
	while (current)
	{
		temp = current->snext;
		free(current->key);
		free(current->value);
		free(current);
		current = temp;
	}
	free(ht->array);
	free(ht);
}
