/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergesort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 01:35:54 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 21:01:03 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flist	*ls_mergesort(t_flist *flist, size_t len, uint16_t options)
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
	left = ls_mergesort(left, len / 2, options);
	right = ls_mergesort(right, (len / 2) + remainder, options);
	return (ls_merge(left, right, options));
}

t_flist	*ls_merge(t_flist *left, t_flist *right, uint16_t options)
{
	t_flist	*result;

	result = NULL;
	while (left && right)
	{
		if (g_compare[(options & MASK_SORT) >> 4](left, right) < 0)
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
