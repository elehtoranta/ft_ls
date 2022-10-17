/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:04:25 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 04:27:18 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	format(t_options *op, t_flist *flist, const char *path)
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
