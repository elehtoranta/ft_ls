/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:26:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/01 12:22:35 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_error(const char *errormsg)
{
	perror(errormsg);
	exit(EXIT_FAILURE);
}

static void	init_options(t_options *op)
{
	op->options = 0;
}

int	main(int argc, char **argv)
{
	t_options	options;

	if (argc < 2)
	{
	// TODO default no options for current dir, NOT ERROR
		printf("usage: [%s]\n", OPTION_CHARS);
		return (0);
	}
	init_options(&options);
	// Send full list of arg strings
	argv = parse_options(&options, &argv[1], &argc);
	if (argc)
		list(&options, argv, argc);

	return (EXIT_SUCCESS);
}
