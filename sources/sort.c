/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:59:21 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/03 21:31:43 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define N_SORTF 1

static void	st_tolower(char *c)
{
	*c = ft_tolower(*c);
}

/* Format strings ready for lexicographical comparison. '.', '..'
 * and hidden files (.*) get special treatment. The comparison is
 * also case agnostic.
 */
static const char	*lex_strip(char *str)
{
	char	*stripped;

	stripped = NULL;
	if (str[0] == '.' && !(ft_strequ(str, ".") || ft_strequ(str, "..")))
		stripped = ft_strdup(str + 1);
	else
		stripped = ft_strdup(str);
	if (!stripped)
		return (NULL);
	ft_striter(stripped, st_tolower);
/*#define DEBUG*/
#ifdef DEBUG
	ft_printf("String '%s' stripped: %s\n", str, stripped);
#endif
	return (stripped);
}

static int	lex_cmp(t_flist *first, t_flist *second)
{
	const char	*first_name = lex_strip(first->dirent->d_name);
	const char	*second_name = lex_strip(second->dirent->d_name);
	int			comparison;

	if (!first_name || !second_name)
		ls_error("Allocation error in comparison function");
	comparison = ft_strcmp(first_name, second_name);
	free((void *)first_name);
	free((void *)second_name);
	return (comparison);
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
	sorter	*compare[N_SORTF] = { lex_cmp };
	t_flist	*flist;
	t_flist	*prev;

	flist = *head;
	prev = *head;
	while (flist->next)
	{
		if (compare[op->options & MASK_SORT](flist, flist->next) > 0)
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
