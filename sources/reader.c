/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 19:11:34 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	add_stat(t_flist *fnode, const char *dir, t_options *op)
{
	t_stat	stat;
	char	*path;

	path = ft_strdjoin(dir, "/", fnode->filename);
	if (!path)
		ls_critical_error("Path allocation failed");
	if (lstat(path, &stat) == -1)
	{
		ls_read_error("", fnode->filename, op, E_MINOR);
		fnode->stat = NULL;
		free(path);
		return ;
	}
	fnode->stat = (t_stat *)malloc(sizeof(stat));
	if (!fnode->stat && errno == ENOMEM)
		ls_critical_error("Stat allocation failed");
	ft_memcpy(fnode->stat, &stat, sizeof(stat));
	free(path);
}

static t_flist	*get_fnode(t_options *op, char *filename, const char *path)
{
	t_flist	*fnode;

	if (!filename)
		ls_critical_error("Invalid filename in get_fnode()");
	fnode = init_fnode();
	if (!fnode)
		ls_critical_error("Initializing file node failed");
	fnode->filename = ft_strdup(filename);
	if (!fnode->filename)
		ls_critical_error("Allocating memory to file name failed");
	if (errno == ENOMEM)
		ls_critical_error("File name allocation failed");
	if (op->options & (O_LONG | MASK_TIME | O_REC))
		add_stat(fnode, path, op);
	return (fnode);
}

static t_flist	*collect_flist(t_flist **head, DIR *dirp, const char *path, t_options *op)
{
	t_flist		*fnode;
	t_flist		*last;
	t_dirent	*dirent;

	last = NULL;
	while (1)
	{
		dirent = readdir(dirp);
		if (errno == EBADF)
			ls_critical_error("Reading directory stream failed");
		if (!dirent)
			return (*head);
		if (dirent->d_name[0] == '.' && !(op->options & O_ALL))
			continue ;
		fnode = get_fnode(op, dirent->d_name, path);
		if (*head == NULL)
			*head = fnode;
		last = append_flist(&last, fnode);
	}
	return (*head);
}

static void	recurse_directories(t_options *op, char *path, t_flist *flist)
{
	char	*dirpath;

	dirpath = NULL;
	while (flist)
	{
		if (flist->stat != NULL
				&& (flist->stat->st_mode & S_IFMT) == S_IFDIR // TODO Add permission mode checks
				&& !(ft_strequ(flist->filename, ".")
					|| ft_strequ(flist->filename, "..")))
		{
			if (ft_strequ(path, "/"))
				dirpath = ft_strjoin(path, flist->filename);
			else
				dirpath = ft_strdjoin(path, "/", flist->filename);
			if (!dirpath)
				ls_critical_error("Path name allocation failed");
			ft_printf("\n%s:\n", dirpath);
			list(op, dirpath);
		}
		flist = flist->next;
	}
}

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
		if (op->options & (O_LONG | O_MTIME))
			get_unique_forms(flist);
		flist = ls_mergesort(flist, len_flist(flist), op->options);
		if (op->options & O_REV)
			flist = reverse_flist(flist, flist);
		format(op, flist, (const char *)path);
		if (op->options & O_REC)
			recurse_directories(op, path, flist);
		delete_flist(&flist);
	}
	if (closedir(dirp) == -1)
		ls_critical_error("Closing directory stream failed");
}

static void	list_file(t_options *op, char *path)
{
	t_flist	*fnode;
	char	*cond_filename = ft_strrchr(path, '/');

	if (cond_filename != NULL)
	{
		// Separate the path to filename and base by effectively splitting them.
		// 'path' still points to the allocated section, so it can be freed.
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

void	list(t_options *op, char *path)
{
	t_stat	stat;

	if (lstat(path, &stat) == -1)
		ls_read_error("", path, op, E_MAJOR);
	else
	{
		if ((stat.st_mode & S_IFMT) == S_IFDIR)
		{
			if (stat.st_mode & S_IXUSR)
				list_dir(op, path);
		}
		else
		{
			list_file(op, path);
		}
	}
	free(path);
}

void	list_args(t_options *op, char **argv, int argc)
{
	if (argc == 0)
		list(op, ft_strdup("."));
	while (argc--)
		list(op, ft_strdup(*argv++));
}
