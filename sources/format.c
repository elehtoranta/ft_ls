/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:04:25 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 22:43:18 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	format(t_flist *flist, const char *path, t_options *op)
{
	if (op->options & O_LONG)
	{
		print_longform(flist, op, path);
	}
	else
	{
		while (flist)
		{
			ft_printf("%s\n", flist->filename);
			flist = flist->next;
		}
	}
}
