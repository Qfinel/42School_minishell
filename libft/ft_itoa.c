/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:58:59 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/16 13:54:16 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_len(int n)
{
	size_t	i;

	i = 1;
	while (n / 10 != 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*ft_get_str(long int n, int len)
{
	char	*str;
	size_t	i;

	i = 0;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
		i = 1;
	}
	str[len] = '\0';
	while (--len >= (int)i)
	{
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			len;
	long int	i;

	len = ft_find_len(n);
	if (n < 0)
		len++;
	i = n;
	str = ft_get_str(i, len);
	return (str);
}
