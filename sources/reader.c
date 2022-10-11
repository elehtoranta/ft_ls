/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/11 03:25:11 by elehtora         ###   ########.fr       */
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

	path = ft_strdjoin(dir, "/", fnode->filename);
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
			ls_error("Reading directory stream failed");
		if (!dirent)
			return (*head);
		fnode = init_fnode();
		if (!fnode)
			ls_error("Initializing file node failed");
		if (*head == NULL)
			*head = fnode;
		fnode->filename = ft_strdup(dirent->d_name);
		if (!fnode->filename)
			ls_error("Allocating memory to file name failed");
		if (op->options & (O_LONG | MASK_SORT | O_REC))
			add_stat(fnode, path);
		last = append_flist(&last, fnode);
#ifdef DEBUG
		ft_printf("head name: %s\n", (*head)->filename);
#endif
		fnode->cmp_name = lex_strip((*head)->filename);
		if (errno == ENOMEM)
			ls_error("File name allocation failed");
	}
	return (*head);
}

/*static void	test_output(t_flist *flist)*/
/*{*/
	/*while (flist)*/
	/*{*/
		/*ft_printf("%s\n", flist->filename); // TODO replace with real formatting*/
		/*flist = flist->next;*/
	/*}*/
/*}*/

static void	recurse_directories(t_options *op, char *path, t_flist *flist)
{
	char	*dirpath;

	dirpath = NULL;
	while (flist)
	{
		if ((flist->stat->st_mode & S_IFMT) == S_IFDIR // TODO Add permission mode checks
				&& !(ft_strequ(flist->filename, ".")
				|| ft_strequ(flist->filename, "..")))
		{
			dirpath = ft_strdjoin(path, "/", flist->filename);
			if (!dirpath)
				ls_error("Path name allocation failed");
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
	{
		ft_printf("ft_ls: cannot access '%s': ", path);
		perror("");
		return ;
	}
	if (!collect_flist(&flist, dirp, path, op))
		ls_error("File list initialization failed");
	sort(op, &flist);
	format(op, flist);
	if (op->options & O_REC)
		recurse_directories(op, path, flist);
	delete_flist(&flist);
	if (closedir(dirp) == -1)
		ls_error("Closing directory stream failed");
}

/*static void	list_file(t_options *op, char *path)*/
/*{*/
	/*t_flist	*flist;*/

	/*flist = NULL;*/
	/*[>collect_flist;<]*/
/*}*/

void	list(t_options *op, char *path)
{
	t_stat		stat;

	if (lstat(path, &stat) == -1)
		ls_error("stat error");
	if ((stat.st_mode & S_IFMT) == S_IFDIR)
	{
		list_dir(op, path);
	}
	else
	{
		/*format(op, );*/
		/*output();*/
		ft_printf("Yes.\n"); //FIXME placeholder
	}
	free(path);
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
