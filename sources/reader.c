/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/03 15:51:00 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	collect_flist(t_flist **head, DIR *dirp)
{
	t_flist		*fnode;
	t_dirent	*dirent;

	while (1)
	{
		dirent = readdir(dirp);
		if (errno == EBADF)
			ls_error("Reading directory stream failed");
		if (!dirent)
			return ;
		fnode = init_fnode();
		if (!fnode)
			ls_error("Initializing file node failed");
		fnode->dirent = (t_dirent *)malloc(sizeof(*dirent));
		if (!fnode->dirent)
			ls_error("Allocating memory to directory entry failed");
		ft_memcpy(fnode->dirent, dirent, sizeof(*dirent));
		*head = prepend_flist(*head, fnode);
	}
}

static void	test_output(t_flist *head)
{
	while (head)
	{
		ft_printf("%s\n", head->dirent->d_name); // TODO replace with real formatting
		free(head->dirent);
		head = head->next;
	}
}

static void	list(t_options *op, char *path)
{
	DIR			*dirp;
	t_flist		*head;
	int			status;

	head = NULL;
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
	collect_flist(&head, dirp);
	if (!head)
		ls_error("File list initialization failed");
	sort(op, &head);
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
	test_output(head);
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
