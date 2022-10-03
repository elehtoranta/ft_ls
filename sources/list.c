/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:40:58 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/03 15:22:23 by elehtora         ###   ########.fr       */
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
	flist->dirent = NULL;
	flist->stat = NULL;
	flist->next = NULL;
	return (flist);
}

/* Adds the element 'new' as the new head of the file list starting at 'head'.
 */
t_flist	*prepend_flist(t_flist *head, t_flist *new)
{
	if (new == NULL)
		return (NULL);
	if (head != NULL)
		new->next = head;
	return (new);
}

/* Deletes the head of a file list and returns the new head (node after the
 * previous head).
 *
 * NOTE: Returning NULL means we've reached the end of the list. This case
 * needs to be handled in caller to avoid dereferencing a NULL pointer.
 */
t_flist	*pop_flist(t_flist *head)
{
	t_flist	*new_head;

	if (head)
	{
		new_head = head->next;
		free(head);
		return (new_head);
	}
	return (NULL);
}

/* Frees and NULLs (deletes) the entire flist structure.
 */
void	delete_flist(t_flist **head)
{
	while (*head != NULL)
	{
		*head = pop_flist(*head);
	}
}
