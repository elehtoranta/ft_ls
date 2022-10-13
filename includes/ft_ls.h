/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:28:36 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 19:17:25 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <dirent.h>
# include <errno.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include "ft_printf.h"

# define RETURN_SHIFT	12
# define E_MINOR		1
# define E_MAJOR		2
// Options available. Expanded when adding supported options.
# define OPTION_CHARS "lRart"
# define N_OPTIONS 5
# define O_LONG		0x0001
# define O_REC		0x0002
# define O_ALL		0x0004
# define O_REV		0x0008
# define O_MTIME	0x0010

// Sorting options (2 bits == 4 permutations)
# define MASK_SORT	0x0030
# define S_LEX		0x0000
# define S_MTIME	0x0010

// Masking for time option selected. The time displayed in
// long format can represent time modified, created or last
// accessed.
# define MASK_TIME	0x0010 // For future expansion

// Aliasing to reduce typing 'struct' every time on use
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

// Bitfield formatting data
typedef struct	s_options
{
	uint16_t	options;
}				t_options;

// Field width formatting for long format.
// Comments are of form: whitespace before + content + whitespace after
// Whitespace is of course not repeated, but shared between adjecent
// blocks.
# define PERMS_FW	11 // + 1
# define DATE_FW	12 // 1 + 12 + 1
typedef struct		s_longform
{
	nlink_t			hardlinks; // 1 + digits + 1
	off_t			size; // 2 + digits + 1
	char			*author; // 1 + strlen + 2
	char			*group; // 2 + strlen + 2
	char			*date; // reformat date into the right string
	uint32_t		major;
	uint32_t		minor;
}					t_longform;

typedef struct		s_fwidths
{
	size_t			total_blocks;
	uint16_t		links_len;
	uint16_t		author_len;
	uint16_t		group_len;
	uint16_t		size_len;
	uint8_t			major;
	uint8_t			minor;
}					t_fwidths;

typedef struct		s_flist
{
	t_stat			*stat;
	char			*filename;
	t_longform		*lform;
	struct s_flist	*next;
}					t_flist;

// Parser function. Checks the validity of options, and sets the option struct.
char	**parse_options(t_options *op, char **argv, int *argc);

void	list(t_options *op, char *path);
void	list_args(t_options *op, char **argv, int argc);

// File list functions
t_flist	*init_fnode(void);
t_flist	*append_fnode(t_flist **flist, t_flist *new);
t_flist	*append_flist(t_flist **last, t_flist *new);
void	prepend_flist(t_flist **head, t_flist *new);
size_t	len_flist(t_flist *flist);
void	pop_flist(t_flist **head);
void	delete_flist(t_flist **head);

// Long format information gathering
void	get_unique_forms(t_flist *fnode);

// Sorting function dispatcher. Makes use of small utility functions,
// of which some are part of ft library.
#define N_SORTF 2
typedef int	(*t_sorter)(t_flist *first, t_flist *second);
int	lex_cmp(t_flist *first, t_flist *second);
int	mtime_cmp(t_flist *first, t_flist *second);

// Global variable for dispatcher
static const t_sorter	g_compare[N_SORTF] = { lex_cmp, mtime_cmp };
void	swap_items(t_flist *a, t_flist *b, t_flist **head, t_flist **prev);

// Merge sort implementation
t_flist				*ls_merge(t_flist *left, t_flist *right, uint16_t options);
t_flist				*ls_mergesort(t_flist *flist, size_t len, uint16_t options);
//void		sort(t_options *op, t_flist **head);
t_flist				*reverse_flist(t_flist *flist, t_flist *head);

// Output formatter
void		format(t_options *op, t_flist *flist, const char *path);

# define LS_PERMISSIONS 7
// Permission handler
void		print_permissions(t_flist *fnode);

// Error functions
void		ls_read_error(const char *message, const char *path, \
		t_options *op, int status);
void		ls_critical_error(const char *errormsg);

# endif
