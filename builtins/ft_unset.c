/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:35:41 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/23 15:06:11 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_env_vars(t_vars *vars, char **args)
{
	int		i;
	int		j;
	int		counter;
	char	**tmp;

	i = 0;
	j = 1;
	counter = 0;
	if (!args[1])
		return (0);
	while (args[j])
	{
		while (args[j])
		{
			while (vars->envp[i])
			{
				tmp = ft_split(vars->envp[i], '=');
				if (!ft_strncmp(args[j], tmp[0], ft_strlen(args[j]) + 1))
					counter++;
				i++;
				free_strings(tmp);
			}
			i = 0;
			j++;
		}
	}
	return (i);
}

void	ft_unset(t_vars *vars, char **args)
{
	int		i;
	int		j;
	int		x;
	int		new_len;
	char	**tmp;
	char	**new_envp;

	i = 0;
	x = 0;
	j = 1;
	new_len = ft_arr_len(vars->envp) - count_env_vars(vars, args) + 1;
	new_envp = ft_calloc(new_len, sizeof(char **));
	exit_status = 1;
	if (!args[1])
		printf("minishell: unset: not enough arguments\n");
	else
	{
		while (args[j])
		{
			if (ft_strchr(args[j], '='))
				printf("minishell: unset: %s: invalid parameter name\n", args[j]);
			else
			{
				while (vars->envp[i])
				{
					tmp = ft_split(vars->envp[i], '=');
					if (ft_strncmp(args[j], tmp[0], ft_strlen(args[j]) + 1))
					{
						new_envp[x] = ft_strdup(vars->envp[i]);
						x++;
					}
					free_strings(tmp);
					i++;
				}
			}
			i = 0;
			j++;
		}
		free_strings(vars->envp);
		vars->envp = new_envp;
	}
	exit_status = 0;
}
