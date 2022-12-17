/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:31:51 by jtsizik           #+#    #+#             */
/*   Updated: 2022/11/22 18:00:18 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static size_t	ft_wordcount(char const *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 1;
	if (s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c)
			j++;
		i++;
	}
	if (s[0] != c)
		j++;
	return (j);
}

static char	*ft_wordcpy(char const *src, size_t j)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc(sizeof(char) * (j + 1));
	if (!dest)
		return (NULL);
	while (i < j && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char		**dest;
	size_t		size;
	size_t		i;
	size_t		len;
	size_t		n;

	i = 0;
	n = 0;
	if (s == 0)
		return (0);
	size = ft_wordcount(s, c);
	dest = ft_calloc(sizeof(char *), (size + 1));
	if (!dest)
		return (NULL);
	while (i < size && s[n])
	{
		while (s[n] == c)
			n++;
		len = ft_wordlen(&s[n], c);
		dest[i] = ft_wordcpy(&s[n], len);
		n += len;
		i++;
	}
	return (dest);
}
