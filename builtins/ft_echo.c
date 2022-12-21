/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/21 17:07:37 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[1])
		return ((void)printf("\n"), free_cmd(cmd));
	if (!ft_strncmp("-n", cmd->args[1], 3) && !cmd->args[2])
		return (free_cmd(cmd));
	else if (!ft_strncmp("-n", cmd->args[1], 3))
		i++;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp("-n", cmd->args[1], 3))
		printf("\n");
	free_cmd(cmd);
	exit(0);
}
