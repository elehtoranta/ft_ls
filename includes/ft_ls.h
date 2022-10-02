/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:28:36 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/02 12:43:39 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <dirent.h>
# include <errno.h>
# include "ft_printf.h"

// Options available. Expanded when adding supported options.
# define OPTION_CHARS "lRart"
# define N_OPTIONS 5

# define O_LONG		0x0001
# define O_REC		0x0002
# define O_ALL		0x0004
# define O_REV		0x0008
# define O_MTIME	0x0010

// Aliasing to reduce typing 'struct' every time on use
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;

// Bitfield formatting data
typedef struct	s_options
{
	uint32_t	options;
}				t_options;

typedef struct		s_flist
{
	t_dirent		*dirent;
	t_stat			*stat;
	struct s_flist	*next;
}					t_flist;

// Directory stream linked list for recursive (-R) invocations
typedef struct	s_dirplist
{
	DIR			*dirp;
	t_flist		*flist;
	DIR			*next;
}				t_dirplist;

// Parser function. Checks the validity of options, and sets the option struct.
char	**parse_options(t_options *op, char **argv, int *argc);

void	list_args(t_options *op, char **argv, int argc);

// Error wrapper to print perror(msg) and exit(EXIT_FAILURE)
void	ls_error(const char *errormsg);

// File list functions
t_flist	*init_flist(void);
t_flist	*prepend_flist(t_flist *head, t_flist *new);
t_flist	*pop_flist(t_flist *head);

#endif