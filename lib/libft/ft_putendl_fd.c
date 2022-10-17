/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 16:10:57 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 19:50:51 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <unistd.h>

int	ft_putendl_fd(char const *s, int fd)
{
	if (!s)
		return (EOF);
	if (write(fd, s, ft_strlen(s)) == -1 || write(fd, "\n", 1) == -1)
		return (EOF);
	return (0);
}
