/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/01 13:10:16 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	list(t_options *op, char **argv)
{
	DIR			*dirp;
	t_dirent	*dirent;
	int			status;

	// FIXME remove compiler suppressing
	(void)op;

	dirp = opendir(*argv);
	if (!dirp)
		ls_error("Opening directory stream failed");
	while (1)
	{
		dirent = readdir(dirp);
		if (errno == EBADF)
			ls_error("Reading directory stream failed");
		if (!dirent)
			break ;
		// sort()
		// format()
		// if (op->option & O_REC) // Recurse
		// {
			// while (dirplist->dirp)
			// {
			// 	list(dirplist->dirp);
			// 	dirplist->dirp = dirplist->next // Consumes the list
			// }
		// }
		ft_printf("%s\n", dirent->d_name); // TODO replace with real formatting
	}

	status = closedir(dirp);
	if (status == -1)
		ls_error("Closing directory stream failed");
}

/* Iterate through file arguments
 */
void	list_args(t_options *op, char **argv, int argc)
{
	while (argc--)
	{
		list(op, argv);
		argv++;
	}
}
