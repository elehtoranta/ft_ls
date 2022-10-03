/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/03 22:12:57 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// H4CK3RM4N5
static void	st_tolower(char *c)
{
	*c = ft_tolower(*c);
}

/* Format strings ready for lexicographical comparison. '.', '..'
 * and hidden files (.*) get special treatment. The comparison is
 * also case agnostic.
 */
static char	*lex_strip(char *str)
{
	char	*stripped;

	stripped = NULL;
	if (str[0] == '.' && !(ft_strequ(str, ".") || ft_strequ(str, "..")))
		stripped = ft_strdup(str + 1);
	else
		stripped = ft_strdup(str);
	if (!stripped)
		return (NULL);
	ft_striter(stripped, st_tolower);
/*#define DEBUG*/
#ifdef DEBUG
	ft_printf("String '%s' stripped: %s\n", str, stripped);
#endif
	return (stripped);
}

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
		prepend_flist(head, fnode);
		(*head)->cmp_name = lex_strip((*head)->dirent->d_name);
		if (!(*head)->cmp_name)
			return ;
	}
}

static void	test_output(t_flist *head)
{
	while (head)
	{
		ft_printf("%s\n", head->dirent->d_name); // TODO replace with real formatting
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
	delete_flist(&head);
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
