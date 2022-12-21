/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:04:09 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/21 15:32:56 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cmd(t_vars *vars, char *input)
{
	char	*cmd;
	char	**args;
	int		id;
	// char	**pasrsed_input;


	if (is_redirect(input))
		return (handle_redirect(vars, input));
	input = remove_unclosed_quotes(input);
	args = split_with_quotes(input);
	// args = ft_split(input, ' ');
	if (!args[0])
		return(free(args));
	if (is_builtin(vars, input, args))
		return ;
	if (args[0][0] == '/')
	{
		if (access(args[0], F_OK) == 0)
			cmd = ft_strdup(args[0]);
		else
			cmd = NULL;
	}
	else
		cmd = get_cmd(vars->paths, args[0]);
	if (cmd)
	{
		id = fork();
		if (id == 0)
			execve(cmd, args, vars->envp);
		wait(NULL);
	}
	else
		printf("minishell: command not found: '%s'\n", args[0]);
	free_strings(args);
	free(cmd);
}

int	count_pipes(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (vars->input[i])
	{
		if (!ft_strncmp(&vars->input[i], "|", 1))
			j++;
		i++;
	}
	return(j);
}

int count_pipes_outside_quotes(t_vars *vars)
{
	int	i;
	int	j;
	int	quotes;

	i = 0;
	j = 0;
	quotes = 0;
	while (vars->input[i])
	{
		if (vars->input[i] == '\"' || vars->input[i] == '\'')
			quotes = !quotes;
		if (!ft_strncmp(&vars->input[i], "|", 1) && !quotes)
			j++;
		i++;
	}
	return(j);
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
	cmds = split_with_quotes(vars->input);
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
			execute_cmd(vars, vars->input);
			free_strings(cmds);
			free_strings(vars->envp);
			free_strings(vars->paths);
			free(vars->input);
			exit(0);
		}
		if (id != 0)
			wait(NULL);
		close(end[1]);
		tmp = end[0];
		i++;
	}
	close(end[0]);
	free_strings(cmds);
}

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
