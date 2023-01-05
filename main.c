/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:04:09 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/05 15:12:48 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_minishell(t_vars *vars, char *input)
{
	printf("exit\n");
	if (vars->paths)
		free_strings(vars->paths);
	if (input)
		free(input);
	if (vars->envp)
		free_strings(vars->envp);
	exit(g_exit);
}

int	is_real_pipe(char *input, int i)
{
	int	j;
	int	quotes1;
	int	quotes2;

	j = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (j < i)
	{
		if (input[j] == '\'' || input[j] == '\"')
			quotes1++;
		j++;
	}
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quotes2++;
		i++;
	}
	if (quotes1 % 2 > 0 && quotes2 > 0)
		return (0);
	else
		return (1);
}

int	is_piped(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '|' && is_real_pipe(str, i))
			return (1);
		i++;
	}
	return (0);
}

void	minishell_loop(t_vars *vars)
{
	char	*tmp;

	while (1)
	{
		signal(SIGINT, ctrl_c_handler);
		tmp = readline("\033[0;32mminishell$> \033[0;37m");
		if (!tmp)
			close_minishell(vars, NULL);
		vars->input = ft_strtrim(tmp, " ");
		free(tmp);
		if (!ft_strncmp(vars->input, "exit", 4)
			&& (vars->input[4] == ' ' || !vars->input[4]))
			close_minishell(vars, vars->input);
		if (vars->input[0] != 0)
			add_history(vars->input);
		vars->input = replace_envvar_with_value(*vars, vars->input);
		if (vars->input[0] != 0 && !unclosed_quotes(vars->input)
			&& is_piped(vars->input))
			exec_pipes(vars, vars->input);
		else if (vars->input[0] != 0 && !unclosed_quotes(vars->input))
			exec_cmd(vars, vars->input);
		wait(NULL);
		free(vars->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		i;

	if (argc != 1 || !argv)
		return (ft_putstr_fd("Run './minishell' without args ;)\n", 2), -1);
	if (!envp[0])
		return (ft_putstr_fd("Run just './minishell' please\n", 2), -1);
	vars.paths = ft_split(getenv("PATH"), ':');
	i = 0;
	vars.envp = ft_calloc(ft_arr_len(envp) + 1, sizeof(char **));
	if (!vars.envp)
		return (ft_putstr_fd("Malloc failed\n", 2), -1);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "SHLVL", 5))
			vars.envp[i] = ft_strdup("SHLVL=2");
		else
			vars.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	g_exit = 0;
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(&vars);
	return (0);
}
