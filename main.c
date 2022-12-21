/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:04:09 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/21 17:31:00 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_vars *vars)
{
	t_vars	replaced_envvar_with_value;

	while (1)
	{
		vars->input = readline("\033[0;32mminishell$> \033[0;37m");
		if (!vars->input)
		{
			printf("\n");
			close_minishell(vars, 0);
		}
		if (ft_strncmp(vars->input, "exit", 4) == 0
			&& (vars->input[4] == ' ' || !vars->input[4]))
			close_minishell(vars, ft_atoi(vars->input) + 5);
		if (vars->input[0] != 0)
			add_history(vars->input);
		*vars = replace_envvar_with_value(*vars);
		if (!count_pipes_outside_quotes(vars) && vars->input[0] != 0)
			execute_cmd(vars, vars->input);
		else if (vars->input[0] != 0)
			handle_pipes(vars);
		free(vars->input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		i;

	if (argc != 1 || !argv)
		return(ft_putstr_fd("Run './minishell' without args ;)\n", 2), -1);
	vars.paths = ft_split(getenv("PATH"), ':');
	i = 0;
	vars.envp = ft_calloc(ft_arr_len(envp) + 1, sizeof(char **));
	while (envp[i])
	{
		vars.envp[i] = ft_strdup(envp[i]);
		i++;
	}
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(&vars);
	return (0);
}
