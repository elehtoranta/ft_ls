/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 23:54:37 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/12 00:03:08 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

 /*Set return to 2*/
/*void	ls_critical_error()  now ls_error()*/
/*{*/

/*}*/

 /*Set return to 1*/
/*void	ls_noncritical_error()*/
/*{*/

/*}*/

void	ls_read_error(const char *message, const char *path)
{
	ft_printf("\nft_ls: %s%s: ", message, path);
	perror("");
}
