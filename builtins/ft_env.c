/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:35:57 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/07 14:45:36 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*replace_shlvl(char *str)
{
	char	*shlvl;
	char	**tmp;
	char	*tmp1;
	int		level;

	tmp = ft_split(str, '=');
	level = ft_atoi(tmp[1]);
	tmp1 = ft_itoa(level + 1);
	shlvl = ft_strjoin("SHLVL=", tmp1);
	free_strings(tmp);
	free(tmp1);
	return (shlvl);
}

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
		g_exit = 0;
	}
	else
	{
		printf("minishell: env: too many arguments\n");
		g_exit = 1;
	}
}
