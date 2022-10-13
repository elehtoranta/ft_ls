/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longform_unique.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:03:14 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 20:51:44 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define MAJOR_MASK 0x7FF00000
#define MINOR_MASK 0xFFFFF

static t_longform	*init_lform(void)
{
	t_longform	*lform;

	lform = (t_longform *)malloc(sizeof(t_longform));
	if (!lform)
		ls_critical_error("Long format allocation failed");
	lform->hardlinks = 0;
	lform->size = 0;
	lform->author = NULL;
	lform->group = NULL;
	lform->date = NULL;
	lform->major = 0;
	lform->minor = 0;
	return (lform);
}

static void	get_user(t_longform *lform, t_flist *fnode)
{
	t_passwd	*passwd;

	passwd = getpwuid(fnode->stat->st_uid);
	if (!passwd)
		lform->author = ft_itoa(fnode->stat->st_uid);
	else
		lform->author = ft_strdup(passwd->pw_name);
}

static void	get_group(t_longform *lform, t_flist *fnode)
{
	t_group		*group;

	group = getgrgid(fnode->stat->st_gid);
	if (!group)
		lform->group = ft_itoa(fnode->stat->st_gid);
	else
		lform->group = ft_strdup(group->gr_name);
}

static void	get_device_id(t_flist *fnode, t_longform *lform)
{
	lform->major = (fnode->stat->st_rdev & (MAJOR_MASK)) >> 24;
	lform->minor = (fnode->stat->st_rdev & (MINOR_MASK));
}

void	get_unique_forms(t_flist *fnode)
{
	t_longform	*lform;

	while (fnode)
	{
		if (fnode->stat != NULL)
		{
			lform = init_lform();
			get_user(lform, fnode);
			get_group(lform, fnode);
			if (!lform->author || !lform->group)
				ls_critical_error("Allocation of authors or groups failed");
			if ((fnode->stat->st_mode & S_IFMT) == S_IFCHR || \
					(fnode->stat->st_mode & S_IFMT) == S_IFBLK)
				get_device_id(fnode, lform);
			fnode->lform = lform;
		}
		fnode = fnode->next;
	}
}
