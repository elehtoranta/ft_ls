/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmodify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elehtora <elehtora@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:17:41 by elehtora          #+#    #+#             */
/*   Updated: 2022/09/22 22:55:06 by elehtora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
// Replaces the string initial with the result of the function parameter f.
// The string 'initial' is taken to be an heap allocated string, since it's
// freed and reallocated inside this function.
//
// The 'f' function is a string function that returns a heap allocated string.
//
// Returns the resulting NEW string (new pointer) that has been modified
// by function f, or NULL if error occured. If an error occured, the initial
// string is left allocated, and needs to be freed accordingly.
//
// Strmodify is useful in situations where a need arises to make subsequent
// modifications to a string with multiple calls to free() in between.
char	*ft_strmodify(char const *initial, char *(*f)(char const *))
{
	char	*result;

	result = f(initial);
	if (!result)
		return (NULL);
	free((char *)initial);
	return (result);
}
