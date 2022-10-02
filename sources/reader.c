/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/02 15:47:56 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	list(t_options *op, char *path)
{
	DIR			*dirp;
	t_dirent	*dirent;
	int			status;

	// FIXME remove compiler suppressing
	(void)op;

	dirp = opendir(path);
	if (!dirp)
	{
		ft_printf("ft_ls: cannot access '%s': ", path);
		perror("");
		free(path);
		return ;
	}
	while (1)
	{
		dirent = readdir(dirp);
		if (errno == EBADF)
			ls_error("Reading directory stream failed");
		if (!dirent)
			break ;
		// sort(flist)
		// format()
		// output()
		// if (op->option & O_REC) // Recurse
		// {
			// fetch_dirnames(); // to send for recursion (after sort)
			// while (dirplist->dirp)
			// {
			// 	list(dirplist->dirp, ft_strdjoin(path, "/", get_next_dir(flist));
			// 	dirplist->dirp = dirplist->next // Consumes the list
			// }
		// }
		ft_printf("%s\n", dirent->d_name); // TODO replace with real formatting
	}
	free(path);
	status = closedir(dirp);
	if (status == -1)
		ls_error("Closing directory stream failed");
}

/* Iterate through file arguments
 */
void	list_args(t_options *op, char **argv, int argc)
{
	char	*path;

	while (argc--)
	{
		path = ft_strdup(*argv);
		list(op, path);
		argv++;
	}
}
