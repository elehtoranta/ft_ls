/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:26:44 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/14 01:56:40 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	match_option(t_options *op, char *c_option)
{
	static const uint16_t	option_bitflags[N_OPTIONS] = {
		O_LONG, O_REC, O_ALL, O_REV, O_TIME
	};
	int						index;

	index = ft_strchr(OPTION_CHARS, *c_option) - OPTION_CHARS;
	if (option_bitflags[index] & MASK_TIME)
		op->options |= ((op->options & ~MASK_TIME) & option_bitflags[index]);
	else
		op->options |= option_bitflags[index];
}

static void	set_options(const char *option_string, t_options *op)
{
	char		*c_option;

	while (option_string)
	{
		c_option = ft_strpbrk(option_string, OPTION_CHARS);
		if (c_option == NULL)
			break ;
		match_option(op, c_option);
		option_string++;
	}
	select_time_mode(op);
}

static void	print_usage(const char nonvalid_char)
{
	ft_printf("ft_ls: illegal option -- %c\n", nonvalid_char);
	ft_printf("usage: ft_ls [%s] [file ...]\n", OPTION_CHARS);
	exit(E_MINOR);
}

/* Need to check if the option string contains illegal options to throw 'illegal
 * option' error.
 */
static char	*validate(const char *option_string)
{
	const size_t	chars_until_unfit = ft_strspn(option_string, OPTION_CHARS);

	if (chars_until_unfit < ft_strlen(option_string))
		return ((char *)&option_string[chars_until_unfit]);
	return (NULL);
}

/* Parse options. Options can be chained -<char...char> or given separately
 * <-char -char...>. Literal -- means end of option arguments.
 *
 * Returns pointer to the first argument that wasn't an option argument
 * and should be interpreted as input parameter (i.e. file).
 */
char	**parse_options(t_options *op, char **argv, int *argc)
{
	char	*non_valid;

	while ((*argc)-- > 1)
	{
		if (*argv[0] != '-' || ft_strequ(*argv, "--"))
			break ;
		non_valid = validate(*argv + 1);
		if (non_valid)
			print_usage(*non_valid);
		set_options(*argv + 1, op);
		argv++;
	}
	if (ft_strequ(*argv, "--") == 1)
	{
		*argc -= 1;
		argv += 1;
	}
	return (argv);
}
