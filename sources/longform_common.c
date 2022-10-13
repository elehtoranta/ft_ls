/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longform_common.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:05:31 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 20:40:32 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_fwidths(t_fwidths *fwidths)
{
	fwidths->links_len = 0;
	fwidths->author_len = 0;
	fwidths->group_len = 0;
	fwidths->size_len = 0;
	fwidths->total_blocks = 0;
	fwidths->major = 0;
	fwidths->minor = 0;
}

/* Gets the common attributes for the long format, so that the field widths
 * can be aligned correctly.
 */
void	get_common_widths(t_fwidths *fwidths, t_flist *flist)
{
	init_fwidths(fwidths);
	while (flist)
	{
		if (flist->stat != NULL)
		{
			if (ft_count_digs(flist->stat->st_nlink) > fwidths->links_len)
				fwidths->links_len = ft_count_digs(flist->stat->st_nlink);
			if (ft_strlen(flist->lform->author) > fwidths->author_len)
				fwidths->author_len = ft_strlen(flist->lform->author);
			if (ft_strlen(flist->lform->group) > fwidths->group_len)
				fwidths->group_len = ft_strlen(flist->lform->group);
			if (ft_count_digs(flist->stat->st_size) > fwidths->size_len)
				fwidths->size_len = ft_count_digs(flist->stat->st_size);
			if (ft_count_digs(flist->lform->major) > fwidths->major)
				fwidths->major = ft_count_digs(flist->lform->major);
			if (ft_count_digs(flist->lform->minor) > fwidths->minor)
				fwidths->minor = ft_count_digs(flist->lform->minor);
			fwidths->total_blocks += flist->stat->st_blocks;
		}
		flist = flist->next;
	}
	if (fwidths->minor > 3)
		fwidths->minor = 3;
}
