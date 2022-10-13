/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:59:21 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 05:10:21 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define N_SORTF 2

/* Swaps places of two items in a flist linked list.
 */
void	swap_items(t_flist *a, t_flist *b, t_flist **head, t_flist **prev)
{
	const t_flist	*tail = b->next; //tail, can be NULL;

	b->next = a;
	if (a == *head)
		*head = a->next;
	else
		(*prev)->next = a->next;
	a->next = (t_flist *)tail;
}

/* Reverses the given list 'flist' (by reversing the direction of pointers)
 * and returns the new head. Used with -r flag.
 */
t_flist	*reverse_flist(t_flist *flist, t_flist *head)
{
	t_flist	*next;
	t_flist	*next_over;

	if (!flist->next) // single element
		return (flist);
	else if (!flist->next->next) // two elements
	{
		swap_items(flist, flist->next, &head, &flist);
		return (head);
	}
	next = flist->next;
	next_over = next->next;
	while (next_over)
	{
		if (flist == head)
			flist->next = NULL;
		next->next = flist;
		flist = next;
		next = next_over;
		next_over = next->next;
	}
	next->next = flist;
	return (next);
}
