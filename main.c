/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:04:09 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/15 13:10:19 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_num(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-' && str[0] != '+' && !ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	check_exit(char *input)
{
	char	**tmp;

	tmp = ft_split(input, ' ');
	if (tmp[1] && !is_num(tmp[1])
		&& !ft_strncmp("exit", tmp[0], 5))
	{
		printf("exit: %s: numeric arg required\n", tmp[1]);
		g_exit = 255;
	}
	else if (tmp[1] && tmp[2] && !ft_strncmp("exit", tmp[0], 5))
	{
		printf("exit: too many args\n");
		g_exit = 1;
	}
	else if (tmp[1] && is_num(tmp[1])
		&& !ft_strncmp("exit", tmp[0], 5))
		g_exit = ft_atoi(tmp[1]);
	free_strings(tmp);
}

void	minishell_loop(t_vars *vars)
{
	char	*tmp;

	while (1)
	{
		signal(SIGINT, ctrl_c_handler);
		hide_signals();
		tmp = readline("\033[0;32mminishell$> \033[0;37m");
		if (!tmp)
			close_minishell(vars, NULL);
		vars->input = ft_strtrim(tmp, " ");
		free(tmp);
		if (!ft_strncmp(vars->input, "exit", 4)
			&& (vars->input[4] == ' ' || !vars->input[4]))
			close_minishell(vars, vars->input);
		if (vars->input[0])
			add_history(vars->input);
		vars->input = replace_envvar_with_value(*vars, vars->input);
		if (vars->input[0] != 0 && !unclosed_quotes(vars->input))
			pipe_loop(vars, vars->input);
		while (wait(NULL) > 0)
			continue ;
		delete_tmp(vars);
		free(vars->input);
	}
}

void	get_env_i(t_vars *vars)
{
	char	*tmp;

	free(vars->envp);
	vars->envp = ft_calloc(4, sizeof(char *));
	tmp = getcwd(NULL, 0);
	vars->envp[0] = ft_strjoin("PWD=", tmp);
	free(tmp);
	vars->envp[1] = ft_strdup("SHLVL=1");
	vars->envp[2] = ft_strdup("_=/Users/jtsizik/Desktop/Projects/\
42School_minishell/./minishell");
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		i;

	if (argc != 1 || !argv)
		return (ft_putstr_fd("Run './minishell' without args ;)\n", 2), -1);
	vars.paths = ft_split(getenv("PATH"), ':');
	i = 0;
	vars.envp = ft_calloc(ft_arr_len(envp) + 1, sizeof(char *));
	if (!vars.envp)
		return (ft_putstr_fd("Malloc failed\n", 2), -1);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
			vars.envp[i] = replace_shlvl(envp[i]);
		else
			vars.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	if (!envp[0])
		get_env_i(&vars);
	g_exit = 0;
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(&vars);
	return (0);
}
