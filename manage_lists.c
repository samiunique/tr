#include "shell.h"

/**
 * add_node_start - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_stru *add_node_start(list_stru **head, const char *str, int num)
{
	list_stru *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_stru));
	if (!new_head)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_stru));
	new_head->num = num;
	if (str)
	{
		new_head->str = duplicate_strings(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */
list_stru *add_node_end(list_stru **head, const char *str, int num)
{
	list_stru *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_stru));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_stru));
	new_node->num = num;
	if (str)
	{
		new_node->str = duplicate_strings(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_strutr - prints only the str element of a list_stru linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_strutr(const list_stru *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_stru **head, unsigned int index)
{
	list_stru *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_stru **head_ptr)
{
	list_stru *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
