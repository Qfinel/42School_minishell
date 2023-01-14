/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 17:34:04 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 17:39:05 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_export_vars(t_vars *vars, char **new_envp)
{
	char	**tmp;
	int		i;

	i = 0;
	while (vars->envp[i])
	{
		if (ft_strncmp("_=", vars->envp[i], 2))
		{
			tmp = ft_split(vars->envp[i], '=');
			if (tmp[1][0] == '\'' && tmp[1][1] == '\'' && !tmp[1][2])
				printf("declare -x %s\n", tmp[0]);
			else
				printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
			free_strings(tmp);
		}
		i++;
	}
	free(new_envp);
}

int	already_exist(char **envp, char *arg)
{
	int		i;
	char	**tmp;

	i = 0;
	while (envp[i])
	{
		tmp = ft_split(envp[i], '=');
		if (!ft_strncmp(arg, tmp[0], ft_strlen(arg) + 1))
		{
			free_strings(tmp);
			return (1);
		}
		i++;
		free_strings(tmp);
	}
	return (0);
}
