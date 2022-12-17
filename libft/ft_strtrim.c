/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:07:53 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/15 12:19:52 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_start_end(size_t num, size_t mark,
							char const *s, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (num == 0 && mark == 1)
			return (num);
		if (mark == 1 && s[num] == set[i])
		{
			num--;
			i = -1;
		}
		if (mark == 0 && s[num] == set[i])
		{
			num++;
			i = -1;
		}
		i++;
	}
	return (num);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	i = 0;
	start = ft_start_end(0, 0, s1, set);
	end = ft_start_end(ft_strlen(s1) - 1, 1, s1, set);
	if (start <= end)
		str = malloc((end - start + 2) * sizeof(char));
	else
		str = malloc(1 * sizeof(char));
	if (!str)
		return (NULL);
	while (start < end + 1)
	{
		str[i] = s1[start];
		i++;
		start++;
	}
	str[i] = '\0';
	return (str);
}
