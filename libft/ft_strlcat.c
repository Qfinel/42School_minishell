/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:27:34 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/18 14:45:12 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	src_len;
	size_t	dst_len;

	if (!dst && dstsize == 0)
		return (0);
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = dst_len;
	j = 0;
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	if (dstsize > 0)
	{
		while (src[j] && i < dstsize - 1)
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
	}
	return (dst_len + src_len);
}
