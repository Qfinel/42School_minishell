/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:35:01 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/02 16:23:29 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	ft_wordlen(char *s, char c)
{
	size_t	i;

	i = 0;
	while ((s[i] && s[i] != c) || (s[i] && s[i] == c && !is_real_pipe(s, i)))
		i++;
	return (i);
}

static size_t	ft_wordcount(char *s, char c)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 1;
	if (s[0] == '\0')
		return (0);
	while (s[i])
	{
		if (s[i - 1] == c && s[i] != c && is_real_pipe(s, i - 1))
			j++;
		i++;
	}
	if (s[0] != c)
		j++;
	return (j);
}

static char	*ft_wordcpy(char *src, size_t j)
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

char	**ft_split_pipes(char *s)
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
	size = ft_wordcount(s, '|');
	dest = ft_calloc(sizeof(char *), (size + 1));
	if (!dest)
		return (NULL);
	while (i < size && s[n])
	{
		while (s[n] == '|' && is_real_pipe(s, n))
			n++;
		len = ft_wordlen(&s[n], '|');
		dest[i] = ft_wordcpy(&s[n], len);
		n += len;
		i++;
	}
	return (dest);
}
