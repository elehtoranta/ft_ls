/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:59:21 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/03 15:51:22 by elehtora         ###   ########.fr       */
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
	/*bool			sorted;*/

	/*sorted = false;*/
	flist = *head;
	/*while (sorted == false)*/
	/*{*/
		/*sorted = true;*/
		while (flist->next)
		{
			prev = flist;
			if (compare[op->options & MASK_SORT](
				flist->dirent->d_name,
				flist->next->dirent->d_name) < 0)
			{
				swap_items(&flist, head, &prev);
				/*sorted = false;*/
				flist = *head;
			}
			else
				flist = flist->next;
		}
	/*}*/
}
