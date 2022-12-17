/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 17:29:57 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/14 17:32:02 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	unsigned int	i;
	char			c;

	i = 0;
	while (s[i])
	{
		c = s[i];
		write(fd, &c, 1);
		i++;
	}
	write(fd, "\n", 1);
}
