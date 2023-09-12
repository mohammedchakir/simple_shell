#include "main.h"

/**
 * addSeparatorAtEnd - Appends a separator node at the end of the list.
 * @head: The head of the list.
 * @sep: The separator node to add.
 * Return: The address of the updated head.
 */
sep_list *addSeparatorAtEnd(sep_list **head, char sep)
{
	sep_list *new_node;
	sep_list *temp_node;

	new_node = malloc(sizeof(sep_list));
	if (new_node == NULL)
		return (NULL);

	new_node->separator = sep;
	new_node->next = NULL;
	temp_node = *head;

	if (temp_node == NULL)
		*head = new_node;
	else
	{
		while (temp_node->next != NULL)
			temp_node = temp_node->next;
		temp_node->next = new_node;
	}

	return (*head);
}

/**
 * freeSeparatorList - Deallocate memory for a list containing separators.
 * @head: The head of the list.
 * Return: None.
 */
void freeSeparatorList(sep_list **head)
{
	sep_list *temp_node;
	sep_list *curr_node;

	if (head != NULL)
	{
		curr_node = *head;
		while ((temp_node = curr_node) != NULL)
		{
			curr_node = curr_node->next;
			free(temp_node);
		}
		*head = NULL;
	}
}

/**
 * appendLineToEnd - Appends the current line to the end of the list.
 * @head: The head of the list.
 * @line: The current line to add.
 * Return: The address of the updated head.
 */
line_list *appendLineToEnd(line_list **head, char *line)
{
	line_list *new_node, *temp_node;

	new_node = malloc(sizeof(line_list));
	if (new_node == NULL)
		return (NULL);

	new_node->line = line;
	new_node->next = NULL;
	temp_node = *head;

	if (temp_node == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp_node->next != NULL)
			temp_node = temp_node->next;
		temp_node->next = new_node;
	}

	return (*head);
}

/**
 * freeLineList - Deallocates memory for the list.
 * @head: The head of the list.
 * Return: None.
 */
void freeLineList(line_list **head)
{
	line_list *temp_node;
	line_list *curr_node;

	if (head != NULL)
	{
		curr_node = *head;
		while ((temp_node = curr_node) != NULL)
		{
			curr_node = curr_node->next;
			free(temp_node);
		}
		*head = NULL;
	}
}
