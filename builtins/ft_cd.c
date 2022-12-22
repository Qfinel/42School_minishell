/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:36:23 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/22 16:27:58 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(t_vars *vars)
{
	int		i;
	char	*old_pwd;
	char	*new_pwd;
	char	**new_envp;

	i = 0;
	while (ft_strncmp(vars->envp[i], "PWD", 3))
		i++;
	old_pwd = ft_strjoin("OLD", vars->envp[i]);
	new_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	i = 0;
	new_envp = ft_calloc(ft_arr_len(vars->envp) + 1, sizeof(char *));
	while (vars->envp[i])
	{
		if (!ft_strncmp(vars->envp[i], "PWD", 3))
			new_envp[i] = new_pwd;
		else if (!ft_strncmp(vars->envp[i], "OLDPWD", 6))
			new_envp[i] = old_pwd;
		else
			new_envp[i] = ft_strdup(vars->envp[i]);
		i++;
	}
	free_strings(vars->envp);
	vars->envp = new_envp;
}

void	ft_cd(t_vars *vars, t_cmd *cmd)
{
	char	*abs_path;
	char	*new_abs_path;

	abs_path = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		abs_path = ft_strjoin("/Users/", getenv("USER"));
		chdir(abs_path);
	}
	else
	{
		if (cmd->args[1][0] != '/')
			abs_path = ft_strjoin(abs_path, "/");
		if (!ft_strncmp(cmd->args[1], "~", 1))
		{
			free(abs_path);
			abs_path = ft_strjoin("/Users/", getenv("USER"));
			new_abs_path = ft_strjoin(abs_path, &cmd->args[1][1]);
		}
		else
			new_abs_path = ft_strjoin(abs_path, cmd->args[1]);
		if (chdir(new_abs_path) < 0)
			if (chdir(cmd->args[1]) < 0)
				printf("minishell: cd: no such file or directory: '%s'\n", cmd->args[1]);
		free(new_abs_path);
	}
	change_pwd(vars);
	free(abs_path);
}
