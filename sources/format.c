/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:04:25 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/11 23:48:23 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*static char	*get_permission_string()*/
/*{*/

/*}*/

/* Gets the common attributes for the long format, so that the field widths
 * can be aligned correctly.
 */
static void	get_common_widths(t_fwidths *fwidths, t_flist *flist)
{
	fwidths->links_len = 0;
	fwidths->author_len = 0;
	fwidths->group_len = 0;
	fwidths->size_len = 0;
	while (flist)
	{
		if (ft_count_digs(flist->stat->st_nlink) > fwidths->links_len)
			fwidths->links_len = ft_count_digs(flist->stat->st_nlink);
		if (ft_strlen(flist->lform->author) > fwidths->author_len)
			fwidths->author_len = ft_strlen(flist->lform->author);
		if (ft_strlen(flist->lform->group) > fwidths->group_len)
			fwidths->group_len = ft_strlen(flist->lform->group);
		if (ft_count_digs(flist->stat->st_size) > fwidths->size_len)
			fwidths->size_len = ft_count_digs(flist->stat->st_size);
		flist = flist->next;
	}
}

/*static void	get_id_info()*/
/*{*/

/*}*/

static t_longform	*init_lform(void)
{
	t_longform	*lform;

	lform = (t_longform *)malloc(sizeof(t_longform));
	if (!lform)
		ls_error("Long format allocation failed");
	lform->hardlinks = 0;
	lform->size = 0;
	lform->author = NULL;
	lform->group = NULL;
	lform->date = NULL;
	return (lform);
}

static void	get_unique_forms(t_flist *fnode)
{
	t_longform	*lform;
	t_passwd	*passwd;
	t_group		*group;

	lform = NULL;
	while (fnode)
	{
		lform = init_lform();
		passwd = getpwuid(fnode->stat->st_uid);
		group = getgrgid(fnode->stat->st_gid);
		if (!passwd || !group)
		{
			perror("UID or GID data not found");
			return ;
		}
		lform->author = ft_strdup(passwd->pw_name);
		lform->group = ft_strdup(group->gr_name);
		if (!lform->author || !lform->group)
			ls_error("Allocation of author or group strings failed");
		fnode->lform = lform;
		fnode = fnode->next;
	}
}

static time_t	get_time(t_flist *fnode, t_options *op)
{
	if ((op->options & MASK_TIME) == O_MTIME)
		return (fnode->stat->st_mtime);
	/*else if ((op->options & MASK_TIME) == O_ATIME)*/
	/*return (fnode->stat->st_atime);*/
	/*else if ((op->options & MASK_TIME) == O_CTIME)*/
	/*return (fnode->stat->st_ctime);*/
	return (fnode->stat->st_mtime); // default
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
	ft_memcpy(datebuf, unformatted_date + 4, 6); // Month + Day
#ifdef DEBUG
	ft_printf("Mmm + [d]d: %s\n", datebuf); // FIXME debug
#endif
	ft_memcpy(datebuf + 6, " ", 1);
	if (ft_labs(format_time - time(NULL)) > SECS_IN_6_MONTHS)
		ft_strncat(datebuf, unformatted_date + 19, 5); // Changed from + 20, 4 to accommodate preceding space
	else
		ft_strncat(datebuf, unformatted_date + 11, 5);
	ft_printf("%s", datebuf);
}

#define READLINK_BUFSIZE 1024
static void	resolve_link(t_flist *fnode, const char *base)
{
	ssize_t	ret;
	char	*path;
	char	buf[READLINK_BUFSIZE];

	path = ft_strdjoin(base, "/", fnode->filename);
	if (!path)
		ls_error("Path allocation failed");
	ft_bzero(buf, READLINK_BUFSIZE);
	ret = readlink(path, buf, READLINK_BUFSIZE);
	free(path);
	if (ret == -1)
	{
		perror("\nft_ls: could not resolve link");
		return ;
	}
	ft_printf(" -> %s", buf);
}

static void	print_longform(t_flist *flist, t_options *op, const char *path)
{
	t_fwidths	fwidths;

	get_unique_forms(flist);
	get_common_widths(&fwidths, flist);
	/*print_total_size();*/ // TODO count blocks and their sizes from stats
	while (flist)
	{
		ft_printf("%-*s ", PERMS_FW, "----------"); //FIXME after ft_printf supports *
		ft_printf("%*u ", fwidths.links_len, flist->stat->st_nlink); //FIXME after ft_printf supports *
		ft_printf("%*s  ", fwidths.author_len, flist->lform->author); //FIXME after ft_printf supports *
		ft_printf("%*s  ", fwidths.group_len, flist->lform->group); //FIXME after ft_printf supports *
		ft_printf("%*u ", fwidths.size_len, flist->stat->st_size); //FIXME after ft_printf supports *
		output_date(get_time(flist, op));
		ft_printf(" %s", flist->filename); //FIXME after ft_printf supports *
		if ((flist->stat->st_mode & S_IFMT) == S_IFLNK)
			resolve_link(flist, path);
		ft_printf("\n");
		flist = flist->next;
	}
}

void	format(t_options *op, t_flist *flist, const char *path)
{
	if (op->options & O_LONG)
	{
		print_longform(flist, op, path);
	}
	else
	{
		/*column_format();*/ // Bonus
		while (flist)
		{
			ft_printf("%s\n", flist->filename);
			flist = flist->next;
		}
	}
}
