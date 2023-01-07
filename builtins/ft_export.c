/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:35:23 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/07 12:01:52 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	already_exist(char **envp, char *arg)
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

static void	replace_existed_vars(char **new_envp, char **args)
{
	int		i;
	int		j;
	char	**tmp;
	char	**tmp1;

	i = 0;
	j = 1;
	while (new_envp[i])
	{
		tmp = ft_split(new_envp[i], '=');
		while (args[j])
		{
			tmp1 = ft_split(args[j], '=');
			if (!ft_strncmp(tmp[0], tmp1[0], ft_strlen(tmp[0]) + 1) && tmp1[1])
			{
				free(new_envp[i]);
				new_envp[i] = ft_strdup(args[j]);
			}
			j++;
			free_strings(tmp1);
		}
		j = 1;
		i++;
		free_strings(tmp);
	}
}

static void	add_var(t_vars *vars, char **new_envp, char **args, int i)
{
	char	**tmp;
	int		j;

	j = 1;
	while (vars->envp[i])
	{
		new_envp[i] = ft_strdup(vars->envp[i]);
		i++;
	}
	replace_existed_vars(new_envp, args);
	free_strings(vars->envp);
	while (args[j])
	{
		tmp = ft_split(args[j], '=');
		if (!tmp[1] && !already_exist(new_envp, tmp[0]))
			new_envp[i] = ft_strjoin(args[j], "=\'\'");
		else if (!already_exist(new_envp, tmp[0]))
			new_envp[i] = ft_strdup(args[j]);
		free_strings(tmp);
		i++;
		j++;
	}
	vars->envp = new_envp;
}

static void	get_paths(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->envp[i])
	{
		if (!ft_strncmp(vars->envp[i], "PATH=", 5))
		{
			if (vars->paths)
				free_strings(vars->paths);
			vars->paths = ft_split(&vars->envp[i][5], ':');
			return ;
		}
		i++;
	}
}

void	ft_export(t_vars *vars, char **args)
{
	char	**new_envp;
	int		new_arr_len;
	int		i;

	i = 0;
	new_arr_len = ft_arr_len(vars->envp) + ft_arr_len(args);
	new_envp = ft_calloc(new_arr_len, sizeof(char *));
	if (!new_envp)
		return (ft_putstr_fd("Malloc failed\n", 2),
			close_minishell(vars, vars->input));
	g_exit = 0;
	if (!args[1])
	{
		while (vars->envp[i])
		{
			if (ft_strncmp("_=", vars->envp[i], 2))
				printf("declare -x %s\n", vars->envp[i]);
			i++;
		}
		free(new_envp);
	}
	else
		add_var(vars, new_envp, args, i);
	if (paths_exist(vars->envp))
		get_paths(vars);
}
