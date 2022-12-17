/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:35:23 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/17 15:05:33 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export(t_vars *vars, char **args)
{
	int		i;
	int		j;
	char	**tmp;
	char	**new_envp;
	int		new_arr_len;

	i = 0;
	j = 1;
	new_arr_len = ft_arr_len(vars->envp) + ft_arr_len(args);
	new_envp = ft_calloc(new_arr_len, sizeof(char **));
	if (!args[1])
	{
		while (vars->envp[i])
		{
			printf("%s\n", vars->envp[i]);
			i++;
		}
		free(new_envp);
	}
	else
	{
		while (vars->envp[i])
		{
			new_envp[i] = vars->envp[i];
			i++;
		}
		free(vars->envp);
		while (args[j])
		{
			tmp = ft_split(args[j], '=');
			if (!tmp[1])
				new_envp[i] = ft_strjoin(args[j], "=\'\'");
			else
				new_envp[i] = ft_strdup(args[j]);
			free_strings(tmp);
			i++;
			j++;
		}
		vars->envp = new_envp;
	}
	free_strings(args);
}