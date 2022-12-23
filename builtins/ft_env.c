/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:35:57 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/23 15:06:02 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_vars *vars, char **args)
{
	int	i;

	i = 0;
	if (!args[1])
	{
		while (vars->envp[i])
		{
			printf("%s\n", vars->envp[i]);
			i++;
		}
		exit_status = 0;
	}
	else
	{
		printf("minishell: env: too many arguments\n");
		exit_status = 1;
	}
		
}
