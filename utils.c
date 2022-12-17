/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:38:31 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/17 15:19:55 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_vars *vars, char *input, char **args)
{
	if (!ft_strncmp(args[0], "cd", 3))
		return (ft_cd(args), 1);
	if (!ft_strncmp(args[0], "echo", 5))
		return (ft_echo(input, args), 1);
	if (!ft_strncmp(args[0], "pwd", 4))
		return (ft_pwd(args), 1);
	if (!ft_strncmp(args[0], "export", 7))
		return (ft_export(vars, args), 1);
	if (!ft_strncmp(args[0], "unset", 6))
		return (ft_unset(vars, args), 1);
	if (!ft_strncmp(args[0], "env", 4))
		return (ft_env(vars, args), 1);
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

void	ctrl_c_handler()
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	free_strings(char **strings)
{
	int i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

void	close_minishell(t_vars *vars, int exit_sign)
{
	printf("exit\n");
	if (vars->paths)
		free_strings(vars->paths);
	if (vars->input)
		free(vars->input);
	if (vars->envp)
		free_strings(vars->envp);
	exit(exit_sign);
}

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}