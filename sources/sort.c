/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:59:21 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/06 02:44:30 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define N_SORTF 2

/* Compare strings. Comparison is made either with the formatted strings
 * (cmp_name) or the 'pure' argument names (filename)
 */
static int	lex_cmp(t_flist *first, t_flist *second)
{
	return (ft_strcmp(first->filename, second->filename));
}

static int	mtime_cmp(t_flist *first, t_flist *second)
{
	// TODO placeholder: compare with data from t_stat
	(void)first;
	(void)second;
	return (0); // FIXME
}

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
	sorter	*compare[N_SORTF] = { lex_cmp, mtime_cmp };
	t_flist	*flist;
	t_flist	*prev;

	flist = *head;
	prev = *head;
	while (flist->next)
	{
		if (compare[(op->options & MASK_SORT) >> 8](flist, flist->next) > 0)
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
