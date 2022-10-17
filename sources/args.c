/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 04:14:59 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/18 00:09:47 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	distribute_arglist(t_flist *flist, t_options *op)
{
	while (flist)
	{
		list(flist->path, op, true);
		flist = flist->next;
	}
}

static void	list_arglists(char **argv, int argc, t_options *op)
{
	// TODO Check input options
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
		else if ((stat.st_mode & S_IFMT) != S_IFDIR) // Filelist
			append_fnode(&filelist, get_fnode(*argv, &arg_op));
		else // Dirlist
			append_fnode(&dirlist, get_fnode(*argv, &arg_op));
		argv++;
	}
	distribute_arglist(filelist, op);
	delete_flist(&filelist);
	distribute_arglist(dirlist, op);
	delete_flist(&dirlist);
}

void	list_args(char **argv, int argc, t_options *op)
{
	if (argc == 0)
		list(".", op, false);
	if (argc == 1)
	{
		list(*argv++, op, false);
		argc--;
	}
	if (argc > 0)
		list_arglists(argv, argc, op);
}
