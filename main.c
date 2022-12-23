/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:04:09 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/23 12:43:32 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_minishell(t_vars *vars, int exit_sign, char *input)
{
	printf("exit\n");
	if (vars->paths)
		free_strings(vars->paths);
	if (input)
		free(input);
	if (vars->envp)
		free_strings(vars->envp);
	exit(exit_sign);
}

int	count_pipes(char *input)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '|' && input[i + 1] != '\'' && input[i + 1] != '\"')
			j++;
		i++;
	}
	return (j);
}

void	minishell_loop(t_vars *vars)
{
	char	*input;

	while (1)
	{
		signal(SIGINT, ctrl_c_handler);
		input = readline("\033[0;32mminishell$> \033[0;37m");
		if (!input)
		{
			printf("\n");
			close_minishell(vars, 0, NULL);
		}
		if (ft_strncmp(input, "exit", 4) == 0
			&& (input[4] == ' ' || !input[4]))
			close_minishell(vars, ft_atoi(input + 5), input);
		if (input[0] != 0)
			add_history(input);
		input = replace_envvar_with_value(*vars, input);
		if (!count_pipes(input) && input[0] != 0)
			exec_cmd(vars, input);
		else if (input[0] != 0)
			exec_pipes(vars, input);
		wait(NULL);
		free(input);
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
	while (envp[i])
	{
		vars.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(&vars);
	return (0);
}
