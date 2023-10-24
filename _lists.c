#include "main.h"

/**
 * add_sep_node_end - appends a separator found at the end
 * of a sep_list.
 * @head: the head of linked list.
 * @sep: the separator found (; | &).
 * Return: the address of the head.
 */
sep_list *add_sep_node_end(sep_list **head, char sep)
{
	sep_list *new, *tmp;

	new = malloc(sizeof(sep_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * free_sep_list - Allocates mem to sep_list.
 * @head: the head of linked list.
 * Return: no return printed.
 */
void free_sep_list(sep_list **head)
{
	sep_list *tmp;
	sep_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
 * add_line_node_end - appends a command line at the end
 * of a line_list.
 * @head: the head of linked list.
 * @line: the command line.
 * Return: the address of the head.
 */
line_list *add_line_node_end(line_list **head, char *line)
{
	line_list *new, *tmp;

	new = malloc(sizeof(line_list));
	if (new == NULL)
		return (NULL);

	new->line = line;
	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}

	return (*head);
}

/**
 * free_line_list - allocates mem to line_list.
 * @head: the head of linked list.
 * Return: no return printed.
 */
void free_line_list(line_list **head)
{
	line_list *tmp;
	line_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->next;
			free(tmp);
		}
		*head = NULL;
	}
}
