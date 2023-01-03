/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:38:31 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/02 16:49:20 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_builtin(t_vars *vars, t_cmd *cmd)
{
	if (!ft_strncmp(cmd->args[0], "cd", 3))
		return (ft_cd(vars, cmd), 1);
	if (!ft_strncmp(cmd->args[0], "echo", 5))
		return (ft_echo(cmd), 1);
	if (!ft_strncmp(cmd->args[0], "pwd", 4))
		return (ft_pwd(cmd->args), 1);
	if (!ft_strncmp(cmd->args[0], "export", 7))
		return (ft_export(vars, cmd->args), 1);
	if (!ft_strncmp(cmd->args[0], "unset", 6))
		return (ft_unset(vars, cmd->args), 1);
	if (!ft_strncmp(cmd->args[0], "env", 4))
		return (ft_env(vars, cmd->args), 1);
	return (0);
}

int	contains_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	exit_process(t_vars *vars)
{
	if (vars->paths)
		free_strings(vars->paths);
	if (vars->envp)
		free_strings(vars->envp);
	exit(g_exit);
}
