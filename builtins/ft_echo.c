/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/15 16:48:55 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(char *line, char **args)
{
	int	i;

	i = 5;
	if (!args[1])
		return ((void)printf("\n"), free_strings(args));
	if (!ft_strncmp("-n", args[1], 3) && !args[2])
		return (free_strings(args));
	else if (!ft_strncmp("-n", args[1], 3))
		i += 3;
	while (line[i])
	{
		if (line[i] != '\\' && line[i] != '\'' && line[i] != '\"')
			printf("%c", line[i]);
		i++;
	}
	if (ft_strncmp("-n", args[1], 3))
		printf("\n");
	free_strings(args);
}