/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:55:43 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/08 13:28:18 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_loop(int *tmp_fd, t_vars *vars, char **cmds, int i)
{
	int	id;
	int	end[2];

	pipe(end);
	id = fork();
	if (id == 0)
	{
		dup2(*tmp_fd, 0);
		if (cmds[i + 1])
			dup2(end[1], 1);
		close(end[0]);
		exec_cmd(vars, cmds[i]);
		free_strings(cmds);
		if (g_exit >= 255)
			g_exit /= 256;
		exit_process(vars);
	}
	while (!cmds[i + 1] && wait(&g_exit) > 0)
		continue ;
	if (g_exit >= 255)
		g_exit /= 256;
	close(end[1]);
	*tmp_fd = end[0];
	if (!cmds[i + 1])
		close(end[0]);
}

void	exec_pipes(t_vars *vars, char *input)
{
	char	**cmds;
	t_cmd	*cmd;
	int		i;
	int		tmp_fd;

	i = 0;
	tmp_fd = 0;
	cmds = ft_split_pipes(input);
	signal(SIGINT, ctrl_c_pipe_handler);
	while (cmds[i])
	{
		cmd = parse_cmd(vars, cmds[i]);
		if (cmd->redirs)
			exec_heredoc(cmd->redirs);
		free_cmd(cmd);
		if (!cmds[1])
		{
			exec_cmd(vars, cmds[0]);
			break ;
		}
		pipe_loop(&tmp_fd, vars, cmds, i);
		i++;
	}
	free_strings(cmds);
}
