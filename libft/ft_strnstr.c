/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:03:51 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/15 14:26:10 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!needle[0])
		return ((char *)haystack);
	if (len == 0)
		return (0);
	while (haystack[i] && i < len)
	{
		while (needle[j] && haystack[i + j] && (i + j) < len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
			if (!needle[j])
				return ((char *)(haystack + i));
		}
		j = 0;
		i++;
	}
	return (NULL);
}
