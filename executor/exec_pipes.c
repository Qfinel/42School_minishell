/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:19:16 by sdukic            #+#    #+#             */
/*   Updated: 2022/12/21 17:26:01 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
