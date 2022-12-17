/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:46:02 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/16 10:50:40 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			i;

	i = 0;
	if (start >= ft_strlen(s))
	{
		ptr = malloc(1 * sizeof(char));
		ptr[0] = '\0';
		return (ptr);
	}
	if (len >= ft_strlen(s))
		len = ft_strlen(s);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (i < len && s[start])
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}
