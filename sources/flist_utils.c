/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 20:42:54 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 23:14:04 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t	len_flist(t_flist *flist)
{
	size_t	len;

	len = 0;
	while (flist)
	{
		len++;
		flist = flist->next;
	}
	return (len);
}

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

t_flist	*get_fnode(t_options *op, char *d_name, const char *path)
{
	t_flist	*fnode;
	char	*filename;

	if (d_name)
		filename = ft_strdup(d_name);
	else
		filename = ft_basename(path);
	if (!filename)
		ls_critical_error("Filename allocation failed");
	fnode = init_fnode();
	if (!fnode)
		ls_critical_error("Initializing file node failed");
	fnode->filename = filename;
	if (errno == ENOMEM)
		ls_critical_error("File name allocation failed");
	if (op->options & (O_LONG | MASK_TIME | O_REC | MODE_ARGLIST))
		add_stat(fnode, path, op);
	return (fnode);
}

t_flist	*collect_flist(t_flist **head, DIR *dirp, \
		const char *path, t_options *op)
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
		{
			*head = fnode;
			last = fnode;
		}
		else
			last = append_flist(&last, fnode);
	}
	return (*head);
}

t_flist	*collect_arglist(t_flist **head, char **argv, t_options *op)
{
	t_flist	*fnode;

	fnode = NULL;
	while (*argv)
	{
		fnode = get_fnode(op, NULL, *argv);
		fnode->path = ft_strdup(*argv);
		if (!fnode->path)
			ls_critical_error("Argument path allocation failed");
		append_fnode(head, fnode);
		argv++;
	}
	return (*head);
}
