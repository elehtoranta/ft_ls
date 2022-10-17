/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 04:54:01 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "sorting.h"

/* Steps into reqursion on directory entries, if the recursion option
 * O_REC is set.
 */
static void	recurse_directories(t_options *op, char *path, t_flist *flist)
{
	char	*dirpath;

	dirpath = NULL;
	while (flist)
	{
		if (flist->stat != NULL
			&& (flist->stat->st_mode & S_IFMT) == S_IFDIR
			&& !(ft_strequ(flist->filename, ".")
				|| ft_strequ(flist->filename, "..")))
		{
			if (ft_strequ(path, "/"))
				dirpath = ft_strjoin(path, flist->filename);
			else
				dirpath = ft_strdjoin(path, "/", flist->filename);
			if (!dirpath)
				ls_critical_error("Path name allocation failed");
			list(op, dirpath, true);
		}
		flist = flist->next;
	}
}

/* Applies the given DIRectory stream and lists the directories provided
 * by that stream.
 */
void	list_dir(t_options *op, char *path)
{
	DIR			*dirp;
	t_flist		*flist;

	flist = NULL;
	dirp = opendir(path);
	if (!dirp)
		return (ls_read_error("", path, op, E_MINOR));
	if (collect_flist(&flist, dirp, path, op))
	{
		if (op->options & (O_LONG | O_TIME))
			get_unique_forms(flist);
		flist = sort(flist, op->options, 0);
		format(op, flist, (const char *)path);
		if (op->options & O_REC)
			recurse_directories(op, path, flist);
		delete_flist(&flist);
	}
	if (closedir(dirp) == -1)
		ls_critical_error("Closing directory stream failed");
}

/* Lists a (single) file entry.
 */
static void	list_file(t_options *op, char *path)
{
	t_flist	*fnode;
	char	*cond_filename;

	cond_filename = ft_strrchr(path, '/');
	if (cond_filename != NULL)
	{
		*cond_filename = '\0';
		cond_filename += 1;
		fnode = get_fnode(op, cond_filename, path);
	}
	else
	{
		fnode = get_fnode(op, path, ".");
	}
	if (op->options & O_LONG)
		get_unique_forms(fnode);
	format(op, fnode, (const char *)path);
	delete_flist(&fnode);
}

/* Dispatches for a single file or directory listing function,
 * based on file mode information from lstat(3).
 */
void	list(t_options *op, char *path, bool print_dirprefix)
{
	t_stat	stat;

	if (lstat(path, &stat) == -1)
		ls_read_error("", path, op, E_MAJOR);
	else
	{
		if ((stat.st_mode & S_IFMT) == S_IFDIR)
		{
			if (stat.st_mode & S_IXUSR)
			{
				if (print_dirprefix == true)
					ft_printf("\n%s:\n", path);
				list_dir(op, path);
			}
		}
		else
			list_file(op, path);
	}
	free(path);
}
