/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_basename.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 03:14:38 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 22:56:24 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_basename(const char *path)
{
	char	*i;
	char	*end;

	if (!path || ft_strequ(path, ""))
		return (ft_strdup("."));
	if (!ft_strchr(path, '/'))
		return (ft_strdup(path));
	end = ft_strchr(path, '\0');
	i = end - 1;
	while (*i == '/' && i != path)
		i--;
	if (i == path && *i == '/')
		return (ft_strdup("/"));
	end = i + 1;
	while (*i != '/' && i != path)
		i--;
	if (*i == '/')
		i++;
	return (ft_strndup(i, end - i));
}
