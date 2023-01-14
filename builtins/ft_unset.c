/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:35:41 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 17:18:08 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_env_indexes(char **args, int *indexes, char **envp, int x)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 1;
	while (envp[i])
	{
		while (args[j])
		{
			tmp = ft_split(envp[i], '=');
			if (!ft_strncmp(args[j], tmp[0], ft_strlen(tmp[0]) + 1))
			{
				indexes[x] = i;
				if (i == 0)
					indexes[x] = -1;
				x++;
			}
			free_strings(tmp);
			j++;
		}
		j = 0;
		i++;
	}
}

static void	create_new_envp(char **new_envp, t_vars *vars, int *indexes)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (vars->envp[i])
	{
		if (!contains_index(indexes, i))
		{
			new_envp[x] = ft_strdup(vars->envp[i]);
			x++;
		}
		i++;
	}
	free(indexes);
}

static void	find_and_delete(char **args, char **new_envp,
	t_vars *vars, int arr_len)
{
	int	*indexes;
	int	j;

	indexes = ft_calloc(arr_len + 1, sizeof(int));
	if (!indexes)
		return (ft_putstr_fd("Malloc failed\n", 2),
			close_minishell(vars, vars->input));
	get_env_indexes(args, indexes, vars->envp, 0);
	j = 1;
	g_exit = 0;
	while (args[j])
	{
		if (ft_strchr(args[j], '=') || !args[j][0])
		{
			printf("minishell: unset: %s: invalid parameter name\n",
				args[j]);
			g_exit = 1;
		}
		j++;
	}
	if (ft_arr_len(args) > (ft_intarrlen(indexes) + 1))
		g_exit = 1;
	create_new_envp(new_envp, vars, indexes);
}

int	paths_exist(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (1);
		i++;
	}
	return (0);
}

void	ft_unset(t_vars *vars, char **args)
{
	int		new_len;
	char	**new_envp;
	int		indexes_arr_len;

	g_exit = 1;
	indexes_arr_len = count_env_vars(vars, args);
	new_len = ft_arr_len(vars->envp) - indexes_arr_len + 1;
	new_envp = ft_calloc(new_len, sizeof(char *));
	if (!new_envp)
		return (ft_putstr_fd("Malloc failed\n", 2),
			close_minishell(vars, vars->input));
	find_and_delete(args, new_envp, vars, indexes_arr_len);
	free_strings(vars->envp);
	vars->envp = new_envp;
	if (!paths_exist(vars->envp))
	{
		if (vars->paths)
			free_strings(vars->paths);
		vars->paths = NULL;
	}
}
