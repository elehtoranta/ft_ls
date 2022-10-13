/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 23:02:39 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/14 01:41:53 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORTING_H
# define SORTING_H

# include "ft_ls.h"

// Sorting modes for direct indexing of sorting function
enum	e_sorting_modes
{
	S_LEX,
	S_MTIME,
	S_REVERSE,
};

// Sorting function dispatcher. Makes use of small utility functions,
// of which some are part of ft library.
# define N_SORTF 3

t_flist		*sort(t_flist *flist, uint16_t options, uint8_t mode);
int			lex_cmp(t_flist *first, t_flist *second);
int			mtime_cmp(t_flist *first, t_flist *second);
int			reverse_cmp(t_flist *first, t_flist *second);

typedef int				(*t_sorter)(t_flist *first, t_flist *second);
static const t_sorter	g_compare[N_SORTF] = {
	lex_cmp,
	mtime_cmp,
	reverse_cmp
};

// Merge sort implementation
t_flist		*ls_merge(t_flist *left, t_flist *right, uint8_t mode);
t_flist		*ls_mergesort(t_flist *flist, size_t len, uint8_t mode);
t_flist		*reverse_flist(t_flist *flist, t_flist *head);

#endif
