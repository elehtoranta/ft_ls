/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 14:28:36 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/15 02:03:19 by elehtora         ###   ########.fr       */
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

// Return values. 0 (success) is returned when !(E_MINOR | E_MAJOR)
# define RETURN_SHIFT	12
# define E_MINOR		1
# define E_MAJOR		2

# define MODE_ARGLIST	0x8000

// Options available. Expanded when adding supported options.
# define OPTION_CHARS "lRart"
# define N_OPTIONS	5
# define O_LONG		0x0001
# define O_REC		0x0002
# define O_ALL		0x0004
# define O_REV		0x0008
# define O_TIME		0x0010

// Time based sorting options (MODIFIED IF OPTIONS ARE ADDED)
# define MASK_TIME	0x0F00
# define O_MTIME	0x0100
//# define O_ATIME		0x0200
//# define O_BTIME		0x0300
//# define O_CTIME		0x0400

// Masking for time option selected. The time displayed in
// long format can represent time modified, created or last
// accessed, of which only the first is an implemented
// sorting option here

// Aliasing to reduce typing 'struct' every time on use
typedef struct stat		t_stat;
typedef struct dirent	t_dirent;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

// Bitfield formatting data
typedef struct s_options
{
	uint16_t		options;
}	t_options;

typedef struct s_longform
{
	nlink_t			hardlinks;
	off_t			size;
	char			*author;
	char			*group;
	char			*date;
	uint32_t		major;
	uint32_t		minor;
}	t_longform;

// Field width formatting for long format.
// Comments are of form: whitespace before + content + whitespace after
// Whitespace is of course not repeated, but shared between adjecent
// blocks.
# define PERMS_FW	11
# define DATE_FW	12

typedef struct s_fwidths
{
	uint32_t		total_blocks;
	uint16_t		links_len;
	uint16_t		author_len;
	uint16_t		group_len;
	uint16_t		size_len;
	uint8_t			major;
	uint8_t			minor;
}	t_fwidths;

typedef struct s_flist
{
	t_stat			*stat;
	char			*filename;
	char			*path;
	t_longform		*lform;
	struct s_flist	*next;
}	t_flist;

// Parser function. Checks the validity of options, and sets the option struct.
char		**parse_options(t_options *op, char **argv, int *argc);
void		select_time_mode(t_options *op);

void		list(t_options *op, char *path, bool print_dirprefix);
void		list_args(t_options *op, char **argv, int argc);

// File list functions
t_flist		*init_fnode(void);
t_flist		*get_fnode(t_options *op, char *filename, const char *path);
t_flist		*collect_flist(t_flist **head, DIR *dirp, \
			const char *path, t_options *op);
t_flist		*collect_arglist(t_flist **head, char **argv, t_options *op);
t_flist		*append_fnode(t_flist **flist, t_flist *new);
t_flist		*append_flist(t_flist **last, t_flist *new);
void		pop_flist(t_flist **head);
void		delete_flist(t_flist **head);
size_t		len_flist(t_flist *flist);

// Long format information gathering
void		print_longform(t_flist *flist, t_options *op, const char *path);
void		get_unique_forms(t_flist *fnode);
void		get_common_widths(t_fwidths *fwidths, t_flist *flist);

// Output formatter
void		format(t_options *op, t_flist *flist, const char *path);

// Permission handler
void		print_permissions(t_flist *fnode);

// Error functions
void		ls_read_error(const char *message, const char *path, \
		t_options *op, int status);
void		ls_critical_error(const char *errormsg);

#endif
