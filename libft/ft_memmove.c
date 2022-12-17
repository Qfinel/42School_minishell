/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 14:01:58 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/18 14:35:04 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (0);
	if (dst <= src)
	{
		i = 0;
		while (i < (int)len)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i++;
		}
	}
	else
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
			i--;
		}
	}
	return (dst);
}
