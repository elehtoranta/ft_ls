/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:26:53 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/18 03:25:55 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	init_options(t_options *op)
{
	op->options = 0x0;
	op->error = 0x0;
}

int	main(int argc, char **argv)
{
	t_options	options;

	init_options(&options);
	argv = parse_options(&options, &argv[1], &argc);
	list_args(argv, argc, &options);
	return (options.error);
}
