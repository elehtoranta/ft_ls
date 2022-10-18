/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparisons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 02:11:45 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/18 03:41:14 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Sorting lexicographically in reverse.
 */
int	reverse_cmp(t_flist *first, t_flist *second)
{
	return (!ft_strcmp(first->path, second->path));
}

/* Lexicographical comparison. Default mode of sorting.
 */
int	lex_cmp(t_flist *first, t_flist *second)
{
	return (ft_strcmp(first->path, second->path));
}

/* Sorting by modification time.
 */
int	mtime_cmp(t_flist *first, t_flist *second)
{
	const int	diff = second->stat->st_mtime - first->stat->st_mtime;

	if (diff == 0)
		return (ft_strcmp(first->path, second->path));
	else
		return (diff);
}
