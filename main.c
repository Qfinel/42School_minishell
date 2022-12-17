/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:04:09 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/16 16:55:26 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_vars *vars)
{
	char	*cmd;
	char	**args;
	int		id;

	args = ft_split(vars->input, ' ');
	if (is_builtin(vars, args))
		return ;
	cmd = get_cmd(vars->paths, args[0]);
	if (cmd)
	{
		id = fork();
		if (id == 0)
			execve(cmd, args, vars->envp);
		if (id != 0)
			wait(NULL);
	}
	if (!cmd)
		printf("minishell: command not found: '%s'\n", args[0]);
	free_strings(args);
	free(cmd);
}

int	count_pipes(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->input[i])
	{
		if (!ft_strncmp(&vars->input[i], "|", 1))
			vars->pipes++;
		i++;
	}
	return(vars->pipes);
}

int	count_redirections(t_vars *vars)
{
	int	i;

	i = 0;
	while (vars->input[i])
	{
		if (!ft_strncmp(&vars->input[i], ">", 1))
			vars->redirections++;
		if (!ft_strncmp(&vars->input[i], "<", 1))
			vars->redirections++;
		i++;
	}
	return(vars->redirections);
}

void	handle_pipes(t_vars *vars)
{
	char	**cmds;
	int		end[2];
	int		i;
	int		id;
	int		tmp;

	i = 0;
	tmp = 0;
	cmds = ft_split(vars->input, '|');
	while (cmds[i])
	{
		pipe(end);
		free(vars->input);
		vars->input = ft_strdup(cmds[i]);
		id = fork();
		if (id == 0)
		{
			dup2(tmp, 0);
			if (cmds[i + 1])
				dup2(end[1], 1);
			close(end[0]);
			execute_cmd(vars);
			free_strings(cmds);
			free_strings(vars->envp);
			free_strings(vars->paths);
			free(vars->input);
			exit(0);
		}
		else
			wait(NULL);
		close(end[1]);
		tmp = end[0];
		i++;
	}
	close(end[0]);
	free_strings(cmds);
	vars->pipes = 0;
	vars->redirections = 0;
}

void	minishell_loop(t_vars *vars)
{
	int	id;

	while (1)
	{
		vars->input = readline("\033[0;32mminishell> \033[0;37m");
		if (!vars->input)
		{
			printf("\n");
			close_minishell(vars, 0);
		}
		if (ft_strncmp(vars->input, "exit", 4) == 0
			&& (vars->input[4] == ' ' || !vars->input[4]))
			close_minishell(vars, ft_atoi(vars->input + 5));
		if (vars->input[0] != 0)
			add_history(vars->input);
		if (!count_pipes(vars) && !count_redirections(vars) && vars->input[0] != 0)
			execute_cmd(vars);
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
	vars.pipes = 0;
	vars.redirections = 0;
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell_loop(&vars);
	return (0);
}