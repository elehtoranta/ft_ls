/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:38:13 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 19:54:36 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"

static int	ft_digit(long int n)
{
	return (-9 <= n && n <= 9);
}

int	ft_putnbr_fd(int n, int fd)
{
	long int	ln;

	ln = (long int) n;
	if (!ft_digit(ln))
		ft_putnbr_fd(((int)ln - ((int)ln % 10)) / 10, fd);
	else if (ln < 0)
	{
		if (write(fd, "-", 1) == -1)
			return (EOF);
	}
	if (ln < 0)
		ln *= (-1);
	ln = ln % 10 + '0';
	if (write(fd, &ln, 1) == -1)
		return (EOF);
	return (0);
}
