/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 21:02:34 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/17 01:55:30 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_string.h"

/* Joins path elements 'dirname' (path to parent) and 'basename' (path to file)
 * and returns a heap allocated pathname. If either argument is NULL or an empty
 * string, the function returns a duplicate of the opposite argument (e.g.
 * basename == NULL => return (strdup(dirname)), etc.).
 *
 * Arguments should be clean versions of basename and dirname, as if obtained by
 * basename(3) and dirname(3). For the formatting of these functions, see their
 * respective manuals.
 */
char	*ft_join_path(char *dirname, char *basename)
{
	if (!dirname && !basename)
		return (NULL);
	if (!dirname || ft_strequ(dirname, ""))
		return (ft_strdup(basename));
	if (!basename || ft_strequ(basename, ""))
		return (ft_strdup(dirname));
	dirname = ft_rstrip(dirname, "/");
	if (!dirname)
		return (NULL);
	return (ft_strdjoin(dirname, "/", basename));
}
