/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longform.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:59:33 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 20:27:19 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static time_t	get_time(t_flist *fnode, t_options *op)
{
	if ((op->options & MASK_TIME) == O_MTIME)
		return (fnode->stat->st_mtime);
	return (fnode->stat->st_mtime);
}

/* Format the date to a desired string format. The one received
 * from ctime(3) is not readily usable.
 *
 * Required format: <Mmm> <DD> <HH:MM>
 * Exception: if the time is 6 mo in the past or future, display
 * year instead of HH:MM
 */
#define SECS_IN_6_MONTHS 15778463

static void	output_date(time_t format_time)
{
	const char	*unformatted_date = ctime(&format_time);
	char		datebuf[DATE_FW + 1];

	ft_bzero(datebuf, DATE_FW);
	ft_memcpy(datebuf, unformatted_date + 4, 6);
	ft_memcpy(datebuf + 6, " ", 1);
	if (ft_labs(format_time - time(NULL)) > SECS_IN_6_MONTHS)
		ft_strncat(datebuf, unformatted_date + 19, 5);
	else
		ft_strncat(datebuf, unformatted_date + 11, 5);
	ft_printf("%s", datebuf);
}

#define READLINK_BUFSIZE 1024

static void	resolve_link(t_flist *fnode, const char *base, t_options *op)
{
	char	*path;
	char	buf[READLINK_BUFSIZE];

	path = ft_strdjoin(base, "/", fnode->filename);
	if (!path)
		ls_critical_error("Path allocation failed");
	ft_bzero(buf, READLINK_BUFSIZE);
	if (readlink(path, buf, READLINK_BUFSIZE) == -1)
	{
		ls_read_error("", fnode->filename, op, E_MINOR);
		return (free(path));
	}
	free(path);
	ft_printf(" -> %s", buf);
}

static void	print_sizeblock(t_flist *fnode, t_fwidths *fwidths)
{
	if ((fnode->stat->st_mode & S_IFMT) == S_IFCHR \
			|| (fnode->stat->st_mode & S_IFMT) == S_IFBLK)
	{
		if (fnode->lform->minor > 512)
			ft_printf(" %*u, %#*.8x ", fwidths->major, fnode->lform->major, \
					fwidths->minor, fnode->lform->minor);
		else
			ft_printf(" %*u, %*u ", fwidths->major, fnode->lform->major, \
					fwidths->minor, fnode->lform->minor);
	}
	else
		ft_printf("%*u ", fwidths->size_len, fnode->stat->st_size);
}

void	print_longform(t_flist *flist, t_options *op, const char *path)
{
	t_fwidths	fwidths;

	get_common_widths(&fwidths, flist);
	ft_printf("total %lu\n", fwidths.total_blocks);
	while (flist)
	{
		if (flist->stat != NULL)
		{
			print_permissions(flist);
			ft_printf("%*u ", fwidths.links_len, flist->stat->st_nlink);
			ft_printf("%-*s  ", fwidths.author_len, flist->lform->author);
			ft_printf("%-*s  ", fwidths.group_len, flist->lform->group);
			print_sizeblock(flist, &fwidths);
			output_date(get_time(flist, op));
			ft_printf(" %s", flist->filename);
			if ((flist->stat->st_mode & S_IFMT) == S_IFLNK)
				resolve_link(flist, path, op);
			ft_printf("\n");
		}
		flist = flist->next;
	}
}