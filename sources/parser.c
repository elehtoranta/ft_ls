/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:26:44 by elehtora          #+#    #+#             */
/*   Updated: 2022/09/29 16:45:04 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*static void	match_options(t_options *op, char c_option)*/
/*{*/
	
/*}*/

static void	set_options(const char *option_string, t_options *op)
{
	char	*c_option;

	while (option_string)
	{
		c_option = ft_strpbrk(option_string, OPTION_CHARS);
		if (c_option == NULL)
			break ;
		// need to loop for reading multiple options per string
		// sets index corresponding to char index in OPTION_CHARS
		op->options |= 1 + (ft_strchr(OPTION_CHARS, *c_option) - OPTION_CHARS);
		/*match_option(op, *c_option);*/
		option_string++;
	}
}

static void	print_usage(const char nonvalid_char)
{
	ft_printf("ls: illegal option -- %c\n", nonvalid_char);
	ft_printf("usage: ls [%s] [file...]\n", OPTION_CHARS);
	exit(EXIT_FAILURE);
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
 * <-char -char...>. Literal -- means end of arguments.
 *
 * Returns pointer to the first argument that wasn't an option argument
 * and should be interpreted as input parameter (i.e. file).
 */
#define OPT_BUFSIZE 64 // Option string max size
char	**parse_options(t_options *op, char **argv, int argc)
{
	char	buf[OPT_BUFSIZE];
	char	*non_valid;

	while (argc-- > 1)
	{
		ft_bzero(buf, OPT_BUFSIZE);
		if (*argv[0] != '-' || ft_strequ(*argv, "--"))
			break ;
		ft_strcpy(buf, *argv);
		non_valid = validate(buf + 1);
		if (non_valid)
			print_usage(*non_valid);
		set_options(buf + 1, op);
		argv++;
	}
	return (argv);
}

#ifdef DEBUG
void	 test_parse()
{

}
#endif
