/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dirname.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 03:19:04 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/16 22:56:32 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dirname(const char *path)
{
	char	*end;

	if (!path || ft_strequ(path, "") || !ft_strchr(path, '/'))
		return (ft_strdup("."));
	if (ft_strequ(path, "/"))
		return (ft_strdup("/"));
	end = ft_strchr(path, '\0') - 1;
	while (*end == '/' && end != path)
		end--;
	while (*end != '/' && end != path)
		end--;
	if (end == path)
	{
		if (*end != '/')
			return (ft_strdup("."));
		else
			return (ft_strndup(end, 1));
	}
	while ((end - 1) != path && *end == '/' && *(end - 1) == '/')
		end--;
	return (ft_strndup(path, end - path));
}
