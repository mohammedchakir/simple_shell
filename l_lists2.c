#include "main.h"

/**
 * add_var_end - adds a variable node at the end of the list
 * @head: head of the list.
 * @lvar: length of variable.
 * @val: value of variable.
 * @lval: length of value.
 * Return: address of  head.
 */
r_var *add_var_end(r_var **head, int lvar, char *val, int lval)
{
	r_var *new_node, *temp_node;

	new_node = malloc(sizeof(r_var));
	if (new_node == NULL)
		return (NULL);
	new_node->len_var = lvar;
	new_node->val = val;
	new_node->len_val = lval;
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
 * var_list_free - frees the var list
 * @head: head of the list.
 * Return: Non.
 */
void var_list_free(r_var **head)
{
	r_var *temp_node;
	r_var *curr_node;

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
