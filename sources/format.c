/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:04:25 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/18 03:50:34 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	format(t_flist *flist, t_options *op, char type)
{
	if (op->options & O_LONG)
	{
		print_longform(flist, op, type);
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
