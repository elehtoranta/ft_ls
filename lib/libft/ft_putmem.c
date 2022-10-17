/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putmem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 16:20:36 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 19:51:04 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_string.h"

/* Outputs n characters of *s memory to stdout. Returns EOF on write failure,
 * non-negative (0) on success.
 */
int	ft_putmem(char *s, size_t n)
{
	if (!s)
		return (EOF);
	if (write(1, s, n) == -1)
		return (EOF);
	return (0);
}
