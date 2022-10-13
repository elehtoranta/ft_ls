/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 00:58:39 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/14 01:42:39 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Decides over the time option ([m]odification, [a]ccess, [b]irth, [c]reation)
 * to be used. If multiple are given, the last one specified is used.
 * Time of modification is the default.
 *
 * NOTE: Only modification time (-t) is implemented as of now, see ft_ls.h.
 */
void	select_time_mode(t_options *op)
{
	if (op->options & O_TIME)
	{
		if (!(op->options & MASK_TIME))
			op->options |= O_MTIME;
	}
}
