/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:59:21 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/12 06:13:19 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define N_SORTF 2

/* Reverses the given list 'flist' (by reversing the direction of pointers)
 * and returns the new head. Used with -r flag.
 */
t_flist	*reverse_flist(t_flist *flist, t_flist *head)
{
	t_flist	*next;
	t_flist	*next_over;

	if (!flist->next) // single element
		return (flist);
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
	return (flist);
}

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
