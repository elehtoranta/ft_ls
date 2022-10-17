/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putbits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 15:55:09 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 19:55:12 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <stdint.h>

int	ft_putbits(void *var, unsigned int bytes)
{
	const uint64_t	printvar = *(uint64_t *)var;
	unsigned int	shift;

	shift = bytes * 8;
	while (shift-- > 0)
	{
		if (printvar & 1L << shift)
			ft_putchar('1');
		else
			ft_putchar('0');
		if (shift % 4 == 0 && shift)
			ft_putchar(' ');
		if ((shift) % 8 == 0 && shift)
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
