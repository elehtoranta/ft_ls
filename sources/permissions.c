/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 03:53:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 04:50:17 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define LS_PERMISSIONS 7
#define PERM_CHARS_LEN 9

/* Handles the special cases concerning the execution/search permissions of
 * a given entry, caused by the additional permission layer of set_*_IDs and
 * sticky bits. Overwrites the previously set 'x' if 's' applies.
 */
static void	reset_exec_permissions(t_flist *fnode, char *buf)
{
	const mode_t	mode = fnode->stat->st_mode;

	if (mode & S_ISUID)
	{
		if (!(mode & S_IXUSR))
			buf[2] = 'S';
		else
			buf[2] = 's';
	}
	if (mode & S_ISGID)
	{
		if (!(mode & S_IXGRP))
			buf[5] = 'S';
		else
			buf[5] = 's';
	}
	if (mode & S_ISVTX)
	{
		if (!(mode & S_IXOTH))
			buf[8] = 'T';
		else
			buf[8] = 't';
	}
}

/* Set user, group and world permission chars (hence 'ugw').
 */
static void	set_ugw(t_flist *fnode, char *buf)
{
	static const char	*perm_char_mask = "rwxrwxrwx";
	uint8_t				bit;
	uint8_t				i;

	bit = PERM_CHARS_LEN;
	i = 0;
	while (bit--)
	{
		if (fnode->stat->st_mode & (1 << bit))
			buf[i] = perm_char_mask[i];
		i++;
	}
	if (fnode->stat->st_mode & (S_ISUID | S_ISGID | S_ISVTX))
		reset_exec_permissions(fnode, buf);
}

/* Set the first character of the permission string, denoting file type.
 */
static void	set_filetype(t_flist *fnode, char *buf)
{
	static const int	filetypes[LS_PERMISSIONS] = {
		S_IFIFO, S_IFCHR, S_IFDIR, S_IFBLK, S_IFREG, S_IFLNK, S_IFSOCK
	};
	const char			*permission_chars = "pcdb-ls";
	int					i;

	i = 0;
	while (i < LS_PERMISSIONS)
	{
		if ((fnode->stat->st_mode & S_IFMT) == filetypes[i])
		{
			buf[0] = permission_chars[i];
			return ;
		}
		i++;
	}
}

/* Outputs the permission string at the start of every long
 * listing formatting string.
 */
void	print_permissions(t_flist *fnode)
{
	char	permission_buf[PERMS_FW + 1];

	ft_memset(permission_buf, '-', PERMS_FW - 1);
	permission_buf[PERMS_FW - 1] = ' ';
	permission_buf[PERMS_FW] = '\0';
	set_filetype(fnode, permission_buf);
	set_ugw(fnode, permission_buf + 1);
	ft_printf("%s ", permission_buf);
}
