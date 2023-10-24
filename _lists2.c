#include "main.h"

/**
 * add_rvar_node - appends a variable at the end
 * of a r_var list.
 * @head: the head of linked list.
 * @lvar: the length of the variable.
 * @val: the value of the variable.
 * @lval: the length of the value.
 * Return: the address of the head.
 */
r_var *add_rvar_node(r_var **head, int lvar, char *val, int lval)
{
	r_var *new, *tmp;

	new = malloc(sizeof(r_var));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

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
 * free_rvar_list - Allocates mem to r_var list
 * @head: the head of linked list.
 * Return: no return printed.
 */
void free_rvar_list(r_var **head)
{
	r_var *tmp;
	r_var *current;

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
