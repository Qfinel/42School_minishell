/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 15:03:57 by jtsizik           #+#    #+#             */
/*   Updated: 2022/10/18 16:24:43 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	num;
	int	mult;

	i = 0;
	num = 0;
	mult = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
		|| str[i] == '\v' || str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-')
		mult *= -1;
	if ((str[i] == '-') || (str[i] == '+'))
		i++;
	while (str[i] && ft_isdigit(str[i]) == 1)
		i++;
	i--;
	while (i >= 0 && ft_isdigit(str[i]) == 1)
	{
		num += (str[i] - 48) * mult;
		mult *= 10;
		i--;
	}
	return (num);
}
