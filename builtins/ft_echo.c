/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/06 18:01:41 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_n(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
	{
		g_exit = 0;
		return ((void)printf("\n"));
	}		
	if (!ft_strncmp("-n", cmd->args[1], 3) && !cmd->args[2])
	{
		g_exit = 0;
		return ;
	}
	while (is_n(cmd->args[i]))
		i++;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (!is_n(cmd->args[1]))
		printf("\n");
	g_exit = 0;
}
