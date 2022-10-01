/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:28:36 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/01 09:55:53 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include "ft_printf.h"

// Options available. Expanded when adding supported options.
# define OPTION_CHARS "lRart"
# define N_OPTIONS 5

# define O_LONG		0x0001
# define O_REC		0x0002
# define O_ALL		0x0004
# define O_REV		0x0008
# define O_MTIME	0x0010

typedef struct	s_options
{
	uint32_t	options; // bitfield formatting data
}				t_options;

// Parser function. Checks the validity of options, and sets the option struct.
char	**parse_options(t_options *op, char **argv, int argc);

// Error wrapper to print perror(msg) and exit(EXIT_FAILURE)
void	ls_error(const char *errormsg);

#endif
