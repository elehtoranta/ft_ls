/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 04:14:59 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/18 03:47:39 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "sorting.h"

static void	distribute_arglist(t_flist *flist, t_options *op)
{
	while (flist)
	{
		list(flist->path, op);
		flist = flist->next;
	}
}

static void	construct_arglists(t_flist *filelist, \
		t_flist *dirlist, t_options *op)
{
	filelist = sort(filelist, op->options, 0);
	dirlist = sort(dirlist, op->options, 0);
	distribute_arglist(filelist, op);
	delete_flist(&filelist);
	distribute_arglist(dirlist, op);
	delete_flist(&dirlist);
}

static void	list_arglists(char **argv, int argc, t_options *op)
{
	t_stat		stat;
	t_flist		*filelist;
	t_flist		*dirlist;
	t_options	arg_op;

	filelist = NULL;
	dirlist = NULL;
	arg_op.options = MODE_ARGLIST;
	while (argc--)
	{
		if (lstat(*argv, &stat) == -1)
			ls_read_error("", *argv, op, E_MAJOR);
		else if ((stat.st_mode & S_IFMT) != S_IFDIR)
			append_fnode(&filelist, get_fnode(*argv, &arg_op));
		else
			append_fnode(&dirlist, get_fnode(*argv, &arg_op));
		argv++;
	}
	construct_arglists(filelist, dirlist, op);
}

void	list_args(char **argv, int argc, t_options *op)
{
	if (argc == 0)
		list(".", op);
	if (argc == 1)
	{
		list(*argv++, op);
		argc--;
	}
	/*if (op->options & O_REC)*/
		/*op->options |= MODE_NAMEDIRS;*/
	if (argc > 0)
	{
		op->options |= MODE_NAMEDIRS;
		list_arglists(argv, argc, op);
	}
}
