/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:11:16 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 04:58:44 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "sorting.h"

/* Sort by [m[ac]time], lexicographically [, reversed],
 * in this order. Brackets denote optional sorting parameters.
 * The first call defaults to lexicographical sort (mode 0), if
 * no time sorting option is set.
 *
 * Sorting can be directly accessed by providing a sorting mode. Available
 * modes are defined in 'sorting.h'.
 */
t_flist	*sort(t_flist *flist, uint16_t options, uint8_t mode)
{
	if (!mode)
	{
		if (options & O_TIME)
			flist = ls_mergesort(flist, len_flist(flist), \
					(options & MASK_TIME) >> 8);
		else
			flist = ls_mergesort(flist, len_flist(flist), S_LEX);
		if (options & O_REV)
			flist = ls_mergesort(flist, len_flist(flist), S_REVERSE);
	}
	else
	{
		flist = ls_mergesort(flist, len_flist(flist), mode);
	}
	return (flist);
}

/* A merge sort implementation, that acts on t_flist types. After dividing
 * the given list to sublists of one node, it utilizes ls_merge to apply one
 * of the comparison functions (see sorting.h; comparison.c) to the sublists
 * while ascending the recursion tree.
 */
t_flist	*ls_mergesort(t_flist *flist, size_t len, uint8_t mode)
{
	const int	remainder = len % 2;
	t_flist		*left;
	t_flist		*right;
	size_t		i;

	if (len <= 1)
		return (flist);
	left = NULL;
	right = NULL;
	i = 0;
	while (flist)
	{
		if (i++ < len / 2)
			flist = append_fnode(&left, flist);
		else
			flist = append_fnode(&right, flist);
	}
	left = ls_mergesort(left, len / 2, mode);
	right = ls_mergesort(right, (len / 2) + remainder, mode);
	return (ls_merge(left, right, mode));
}

t_flist	*ls_merge(t_flist *left, t_flist *right, uint8_t mode)
{
	t_flist	*result;

	result = NULL;
	while (left && right)
	{
		if (g_compare[mode](left, right) < 0)
			left = append_fnode(&result, left);
		else
			right = append_fnode(&result, right);
	}
	while (left)
		left = append_fnode(&result, left);
	while (right)
		right = append_fnode(&result, right);
	return (result);
}
