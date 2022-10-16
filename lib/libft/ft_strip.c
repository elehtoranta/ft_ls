/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 03:48:55 by elehtora          #+#    #+#             */
/*   Updated: 2022/10/15 04:29:31 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lstrip(const char *str, const char *charset)
{
	const char	*start = str + ft_strspn(str, charset);

	return (ft_strdup(start));
}

char	*ft_rstrip(const char *str, const char *charset)
{
	const char	*end = ft_strchr(str, '\0') - 1;

	while (ft_strchr(charset, *end))
		end--;
	return (ft_strndup(str, end - str + 1));
}

char	*ft_strip(const char *str, const char *charset)
{
	const char	*start = str + ft_strspn(str, charset);
	const char	*end = ft_strchr(str, '\0') - 1;

	while (ft_strchr(charset, *end))
		end--;
	return (ft_strndup(start, end - start + 1));
}

