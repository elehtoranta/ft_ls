/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 04:14:59 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 22:42:09 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	loop_args(char **argv, int argc, t_options *op, int choose)
{
	t_stat	stat;

	while (argc--)
	{
		if (lstat(*argv, &stat) == -1)
			ls_read_error("", *argv, op, E_MAJOR);
		else if (choose == S_IFREG)
		{
			if ((stat.st_mode & S_IFMT) != S_IFDIR)
				list(ft_strdup(*argv), op, true);
		}
		else
		{
			if ((stat.st_mode & S_IFMT) == S_IFDIR)
				list(ft_strdup(*argv), op, true);
		}
		argv++;
	}
}

void	list_args(char **argv, int argc, t_options *op)
{
	if (argc == 0)
		list(ft_strdup("."), op, false);
	if (argc == 1)
	{
		list(ft_strdup(*argv++), op, false);
		argc--;
	}
	if (argc > 0)
	{
		loop_args(argv, argc, op, S_IFREG);
		loop_args(argv, argc, op, S_IFDIR);
	}
}
