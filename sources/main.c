/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:26:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/09/29 16:34:24 by elehtora         ###   ########.fr       */
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
		printf("Usage: [%s]", OPTION_CHARS);// TODO default no options for current dir
		return (0);
	}
	/*printf("%s\n", argv[libft/1]);*/
	init_options(&options);
	argv = parse_options(&options, &argv[1], argc); // Send full list of arg strings
	ft_printf("Options format integer: %d\n", options.options);

	return (EXIT_SUCCESS);
}
