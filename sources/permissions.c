/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 03:53:18 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/12 01:15:40 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define PERM_CHARS_LEN 9
/* Set user, group and world permission chars (hence 'ugw').
 */
static void	set_ugw(t_flist *fnode, char *buf)
{
	/*ft_printf("%o", fnode->stat->st_mode);*/
	static const char	*perm_char_mask = "rwxrwxrwx";
	uint8_t	bit;
	uint8_t	i;

	bit = PERM_CHARS_LEN;
	i = 0;
	while (bit--)
	{
		if (fnode->stat->st_mode & (1 << bit))
			buf[i] = perm_char_mask[i];
		i++;
	}
}

/* Set the first character of the permission string, denoting file type.
 */
static void	set_filetype(t_flist *fnode, char *buf)
{
	const int	filetypes[LS_PERMISSIONS] = {
		S_IFIFO, S_IFCHR, S_IFDIR, S_IFBLK, S_IFREG, S_IFLNK, S_IFSOCK
	};
	const char	*permission_chars = "pcdb-ls";
	int			i;

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

void	print_permissions(t_flist *fnode)
{
	char	permission_buf[PERMS_FW + 1];

	// Set default state "---------- "
	ft_memset(permission_buf, '-', PERMS_FW - 1);
	permission_buf[PERMS_FW - 1] = ' ';
	permission_buf[PERMS_FW] = '\0';
	set_filetype(fnode, permission_buf);
	set_ugw(fnode, permission_buf + 1);
	ft_printf("%s ", permission_buf);
}

