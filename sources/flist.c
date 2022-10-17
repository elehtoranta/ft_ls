/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:40:58 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 21:14:16 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Creates and initializes a new file list node, returning it.
 */
t_flist	*init_fnode(void)
{
	t_flist	*flist;

	flist = (t_flist *)malloc(sizeof(t_flist));
	if (!flist)
		return (NULL);
	flist->stat = NULL;
	flist->filename = NULL;
	flist->lform = NULL;
	flist->next = NULL;
	return (flist);
}

/* Appends a list item 'new' to the file list 'flist', returning the
 * next node in list 'new' if such exists, NULL otherwise.
 */
t_flist	*append_fnode(t_flist **flist, t_flist *new)
{
	// TODO Check what's the pointer value of flist at *flist == NULL
	t_flist	*rest;
	t_flist	*current;

	rest = NULL;
	if (new == NULL)
		return (new);
	if (new->next != NULL)
		rest = new->next;
	new->next = NULL;
	if (!*flist)
		*flist = new;
	else
	{
		current = *flist;
		while (current->next)
			current = current->next;
		current->next = new;
	}
	return (rest);
}

/* Adds a new list to the end of a list.
 * For performance, the parameter 'last' is passed
 * instead of head, so the whole list is not traversed
 * just for insertion. Yet, the function works (albeit
 * unoptimally) when an earlier node is passed.
 */
t_flist	*append_flist(t_flist **last, t_flist *new)
{
	if (new == NULL)
		return (*last);
	if (*last != NULL)
	{
		while ((*last)->next)
			*last = (*last)->next;
		(*last)->next = new;
	}
	return (new);
}

/* Deletes the head of a file list and returns the new head (node after the
 * previous head).
 *
 * NOTE: Returning NULL means we've reached the end of the list. This case
 * needs to be handled in caller to avoid dereferencing a NULL pointer.
 */
void	pop_flist(t_flist **head)
{
	t_flist	*new_head;

	if (head && *head)
	{
		new_head = (*head)->next;
		free((*head)->stat);
		free((*head)->filename);
		if ((*head)->lform)
		{
			free((*head)->lform->author);
			free((*head)->lform->group);
			free((*head)->lform);
		}
		free(*head);
		*head = new_head;
	}
}

/* Frees and NULLs (deletes) the entire flist structure.
*/
void	delete_flist(t_flist **head)
{
	while (*head != NULL)
		pop_flist(head);
}
