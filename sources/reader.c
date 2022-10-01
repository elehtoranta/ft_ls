/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 11:18:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/01 12:19:18 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	list(t_options *op, char **argv, int argc)
{
	DIR			*dirp;
	t_dirent	*dirent;
	int			status;

	// FIXME remove compiler suppressing
	(void)argc;
	(void)op;

	dirp = opendir(*argv);
	if (!dirp)
		ls_error("Opening directory stream failed");
	while (1)
	{
		dirent = readdir(dirp);
		if (errno == EBADF)
			ls_error("Reading directory stream failed");
		if (!dirent)
			break ;
		/*ft_printf("File name: %s\n", dirent->d_name);*/
	}

	status = closedir(dirp);
	if (status == -1)
		ls_error("Closing directory stream failed");
}
