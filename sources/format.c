/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 02:04:25 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/08 23:54:12 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*static char	*get_permission_string()*/
/*{*/

/*}*/

static int	get_longform(t_longform *longform, t_flist *fnode)
{
	t_passwd	*passwd;
	t_group		*group;

	passwd = getpwuid(fnode->stat->st_uid);
	group = getgrgid(fnode->stat->st_gid);
	if (!passwd || !group)
	{
		perror("UID or GID data not found");
		return (-1);
	}
	longform->hardlinks = (uint32_t)ft_count_digs(fnode->stat->st_nlink);
	longform->size = (uint32_t)ft_count_digs(fnode->stat->st_size);
	longform->author = ft_strdup(passwd->pw_name);
	longform->group = ft_strdup(group->gr_name);
	if (!longform->author || !longform->group)
		ls_error("Allocation of author or group strings failed");
	return (0);
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
	{
		ft_strncat(datebuf, unformatted_date + 20, 4);
	}
	else
	{
		ft_strncat(datebuf, unformatted_date + 11, 5);
	}
	ft_printf("%s", datebuf);
}

void	format(t_options *op, t_flist *flist)
{
	t_longform	fwidths;

	while (flist)
	{
		if (op->options & O_LONG) // TODO 6 mo mtime diff -> ctime then - ctime (secs) now to monts
		{
			/*ft_printf("Do long boi stuff\n"); //FIXME REMOVEME*/
			if (get_longform(&fwidths, flist) == -1)
				break ; // TODO Check this
			printf("%-*s ", PERMS_FW, "----------"); //FIXME after ft_printf supports *
			printf("%*u ", (int)fwidths.hardlinks, flist->stat->st_nlink); //FIXME after ft_printf supports *
			printf("%*s  ", (int)ft_strlen(fwidths.author), fwidths.author); //FIXME after ft_printf supports *
			printf("%*s  ", (int)ft_strlen(fwidths.group), fwidths.group); //FIXME after ft_printf supports *
			output_date(get_time(flist, op));
			/*write(1, date, DATE_FW);*/
			/*printf("%*s ", DATE_FW, ctime(&time)); //FIXME after ft_printf supports * AND conditions if O_mtime != default*/
			printf("%s", flist->filename); //FIXME after ft_printf supports *
			/*printf();*/ // For symlink
			printf("\n");
		}
		else
		{
			/*ft_printf("No long boi stuff\n");*/
			/*column_format();*/
			ft_printf("%s\n", flist->filename);
		}
		flist = flist->next;
	}
}