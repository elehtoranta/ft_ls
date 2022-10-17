/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 05:28:42 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 19:52:42 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "ft_string.h"

int	ft_putstr(char const *s)
{
	if (!s)
		return (EOF);
	if (write(1, s, ft_strlen(s)) == -1)
		return (EOF);
	return (0);
}
