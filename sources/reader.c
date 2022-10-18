/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/18 15:11:02 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "sorting.h"

/* Steps into reqursion on directory entries, if the recursion option
 * O_REC is set.
 */
static void	recurse_directories(t_flist *flist, const char *path, t_options *op)
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
			dirpath = ft_join_path((char *)path, flist->filename);
			if (!dirpath)
				ls_critical_error("Path name allocation failed");
			list(dirpath, op);
			free(dirpath);
		}
		flist = flist->next;
	}
}

/* Applies the given DIRectory stream and lists the directories provided
 * by that stream.
 */
void	list_dir(const char *path, t_options *op)
{
	DIR			*dirp;
	t_flist		*flist;

	flist = NULL;
	dirp = opendir(path);
	if (!dirp)
		return (ls_read_error("", path, op, E_MINOR));
	flist = collect_flist(dirp, path, op);
	if (op->options & MODE_NAMEDIRS)
		ft_printf("\n%s:\n", path);
	if (flist)
	{
		if (op->options & (O_LONG | O_TIME))
			get_unique_forms(flist);
		flist = sort(flist, op->options, 0);
		format(flist, op, 'd');
		if (op->options & O_REC)
			recurse_directories(flist, path, op);
		delete_flist(&flist);
	}
	if (closedir(dirp) == -1)
		ls_critical_error("Closing directory stream failed");
}

/* Lists a (single) file entry.
 */
static void	list_file(const char *path, t_options *op)
{
	t_flist	*fnode;

	fnode = get_fnode(path, op);
	if (op->options & O_LONG)
		get_unique_forms(fnode);
	format(fnode, op, 'f');
	delete_flist(&fnode);
}

/* Dispatches for a single file or directory listing function,
 * based on file mode information from lstat(3).
 */
void	list(char *path, t_options *op)
{
	t_stat	stat;

	if (lstat(path, &stat) == -1)
		ls_read_error("", path, op, E_MAJOR);
	else
	{
		if ((stat.st_mode & S_IFMT) == S_IFDIR)
			list_dir(path, op);
		else
			list_file(path, op);
	}
}
