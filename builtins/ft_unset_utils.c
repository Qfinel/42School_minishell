/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:20:25 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/13 15:29:40 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_index(int *indexes, int i)
{
	int	j;

	j = 0;
	while (indexes[j])
	{
		if (indexes[j] == i)
			return (1);
		else if (indexes[j] == -1 && i == 0)
			return (1);
		j++;
	}
	return (0);
}

int	count_env_vars(t_vars *vars, char **args)
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
	return (counter);
}
