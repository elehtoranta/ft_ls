/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/05 00:13:30 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*#define DEBUG*/
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
		return (NULL);
	if (!stripped)
		return (NULL);
	ft_striter(stripped, st_tolower);
#ifdef DEBUG
	ft_printf("String '%s' stripped: %s\n", str, stripped);
#endif
	return (stripped);
}

static void	add_stat(t_flist *fnode, const char *dir)
{
	t_stat	stat;
	char	*path;

	path = ft_strdjoin(dir, "/", fnode->dirent->d_name);
	if (!path)
		ls_error("Path allocation failed");
#ifdef DEBUG
	ft_printf("Path: %s\n", path);
#endif
	if (lstat(path, &stat) == -1)
		ls_error("Lstat failed");
	fnode->stat = (t_stat *)malloc(sizeof(stat));
	if (!fnode->stat && errno == ENOMEM)
		ls_error("Stat allocation failed");
	ft_memcpy(fnode->stat, &stat, sizeof(stat));
#ifdef DEBUG
	ft_printf("Allocated stat size data: %lu\n", fnode->stat->st_size);
	ft_printf("Allocated stat creation time: %s\n", ctime(&fnode->stat->st_mtime));
#endif
	free(path);
}

static void	collect_flist(t_flist **head, DIR *dirp, const char *path)
{
	t_flist		*fnode;
	t_dirent	*dirent;

	(void)path;
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
		add_stat(fnode, path);
		prepend_flist(head, fnode);
#ifdef DEBUG
		ft_printf("head name: %s\n", (*head)->dirent->d_name);
#endif
		(*head)->cmp_name = lex_strip((*head)->dirent->d_name);
		if (errno == ENOMEM)
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

/*static void	list_file()*/
/*{*/
	/*format()*/
/*}*/

static void	append_dirlist(t_dirlist **head, t_dirlist *new)
{
	t_dirlist	*current;

	current = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

/* Collects directory paths that are sent to recursive listing calls.
 * Special relative directories (. and ..) are excluded since recursing
 * into them would cause infinite listing.
 */
static void	collect_dirnames(t_flist *flist, t_dirlist **dirlist, char *path)
{
	t_dirlist	*dirnode;
	t_dirlist	*head;

	dirnode = NULL;
	head = NULL;
	while (flist)
	{
		if ((flist->stat->st_mode & S_IFMT) == S_IFDIR
				&& !(ft_strequ(flist->dirent->d_name, ".")
				|| ft_strequ(flist->dirent->d_name, "..")))
		{
			dirnode = (t_dirlist *)malloc(sizeof(*dirnode));
			if (!dirnode)
				ls_error("Directory name node allocation failed");
			dirnode->next = NULL;
			dirnode->dirpath = ft_strdjoin(path, "/", flist->dirent->d_name);
			if (!dirnode->dirpath)
				ls_error("Directory path string allocation failed");
			append_dirlist(&head, dirnode);
		}
		flist = flist->next;
	}
	*dirlist = head;
#ifdef DEBUG
	while (head)
	{
		ft_printf("dirpath: %s\n", head->dirpath);
		head = head->next;
	}
#endif
}

static void	list(t_options *op, char *path)
{
	DIR			*dirp;
	t_flist		*flist;
	t_stat		stat;
	t_dirlist	*dirlist;

	if (lstat(path, &stat) == -1)
		ls_error("stat error");
	if (!((stat.st_mode & S_IFMT) == S_IFDIR))
	{
		ft_printf("Yes.\n");
	}
	else
	{
		flist = NULL;
		dirp = opendir(path);
		if (!dirp)
		{
			ft_printf("ft_ls: cannot access '%s': ", path);
			perror("");
			free(path);
			return ;
		}
		collect_flist(&flist, dirp, path);
		if (!flist)
			ls_error("File list initialization failed");
		sort(op, &flist);
		// format()
		// output()
		test_output(flist);
		if (op->options & O_REC)
		{
			collect_dirnames(flist, &dirlist, path); // to send for recursion (after sort)
			while (dirlist)
			{
				ft_printf("\n%s:\n", dirlist->dirpath);
				list(op, dirlist->dirpath);
				dirlist = dirlist->next; // Consumes the list; FIXME Leaks, no free anywhere.
			}
		}
		delete_flist(&flist);
		free(path);
		if (closedir(dirp) == -1)
			ls_error("Closing directory stream failed");
	}
}

/* Iterate through file arguments
 */
void	list_args(t_options *op, char **argv, int argc)
{
	char	*path;

	// No file/directory arguments
	if (argc == 0)
		list(op, ft_strdup("."));
	while (argc--)
	{
		path = ft_strdup(*argv);
		list(op, path);
		argv++;
	}
}
