/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:54:37 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/18 02:50:56 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Non-recoverable error. Return value of 2.
 */
void	ls_critical_error(const char *errormsg)
{
	perror(errormsg);
	exit(E_MAJOR);
}

/* Recoverable, minor error. Sets return value to 1.
 */
void	ls_read_error(const char *message, const char *path, \
		t_options *op, int status)
{
	op->error = status;
	ft_printf("ft_ls: %s%s: ", message, path);
	perror("");
}
