/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:36:23 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/11 12:01:19 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_old_pwd(t_vars *vars)
{
	int		i;
	char	*old_pwd;

	i = 0;
	while (ft_strncmp(vars->envp[i], "PWD", 3))
		i++;
	old_pwd = ft_strjoin("OLD", vars->envp[i]);
	return (old_pwd);
}

static int	change_pwd(t_vars *vars)
{
	int		i;
	char	*old_pwd;
	char	*new_pwd;
	char	**new_envp;

	i = 0;
	new_envp = ft_calloc(ft_arr_len(vars->envp) + 1, sizeof(char *));
	if (!new_envp)
		return (-1);
	old_pwd = get_old_pwd(vars);
	new_pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
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
	return (0);
}

static int	is_all_slashes(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] != '/')
			return (0);
		i++;
	}
	return (1);
}

static void	go_to_dir(t_cmd *cmd, char *abs_path)
{
	char	*new_abs_path;

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
	free(abs_path);
	if (cmd->args[1][0] == '/' || chdir(new_abs_path) < 0)
	{
		if (chdir(cmd->args[1]) < 0)
		{
			printf("minishell: cd: %s: No such file or directory\n",
				cmd->args[1]);
			g_exit = 1;
		}
	}
	free(new_abs_path);
}

void	ft_cd(t_vars *vars, t_cmd *cmd)
{
	char	*abs_path;
	char	*tmp;

	g_exit = 0;
	abs_path = getcwd(NULL, 0);
	if (!cmd->args[1])
	{
		abs_path = ft_strjoin("/Users/", getenv("USER"));
		chdir(abs_path);
	}
	else if (is_all_slashes(cmd->args[1]))
		chdir("/");
	else if (!ft_strncmp(cmd->args[1], "-", 2))
	{
		tmp = get_env_value(vars, "OLDPWD");
		chdir(tmp);
		free(tmp);
	}
	else
		go_to_dir(cmd, abs_path);
	if (change_pwd(vars) < 0)
		return (ft_putstr_fd("Malloc failed\n", 2),
			close_minishell(vars, vars->input));
}
