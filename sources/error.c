/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:54:37 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/13 19:17:49 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_critical_error(const char *errormsg)
{
	perror(errormsg);
	exit(E_MAJOR);
}

void	ls_read_error(const char *message, const char *path, \
		t_options *op, int status)
{
	op->options |= (status << RETURN_SHIFT);
	ft_printf("\nft_ls: %s%s: ", message, path);
	perror("");
}
