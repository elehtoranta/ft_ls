/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:59:21 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/03 20:10:56 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define N_SORTF 1

/* Swaps places of two items in a flist linked list.
 */
static void	swap_items(t_flist **first, t_flist **head, t_flist **prev)
{
	const t_flist	*tail = (*first)->next->next; //tail, can be NULL;

	(*first)->next->next = *first;
	if (*first == *head)
		*head = (*first)->next;
	else
		(*prev)->next = (*first)->next;
	(*first)->next = (t_flist *)tail;
}

/* Sorting file names. Dispatching to a sorting function based on the index
 * saved at the op->option bitfield.
 */
void	sort(t_options *op, t_flist **head)
{
	sorter	*compare[N_SORTF] = { ft_strcmp };
	t_flist			*flist;
	t_flist			*prev;

	(void)op;
	(void)compare;
	flist = *head;
	prev = *head;
	while (flist->next)
	{
		if (compare[op->options & MASK_SORT](
			flist->dirent->d_name,
			flist->next->dirent->d_name) > 0)
		{
			swap_items(&flist, head, &prev);
			flist = *head;
		}
		else
		{
			prev = flist;
			flist = flist->next;
		}
	}
}
