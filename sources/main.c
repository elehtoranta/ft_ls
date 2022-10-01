/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:26:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/01 10:22:45 by elehtora         ###   ########.fr       */
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
		printf("usage: [%s]\n", OPTION_CHARS);// TODO default no options for current dir
		return (0);
	}
	init_options(&options);
	argv = parse_options(&options, &argv[1], argc); // Send full list of arg strings
#ifdef DEBUG
	ft_printf("Options format integer: %d\n", options.options);
#endif

	return (EXIT_SUCCESS);
}
