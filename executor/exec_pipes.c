/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:55:43 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 16:37:48 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	exec_pipes(t_vars *vars, t_pipes *pipes, t_pipes *to_free)
{
	if (fork() == 0)
	{
		if (pipes->infd != 0)
			dup2(pipes->infd, 0);
		if (pipes->outfd != 1)
			dup2(pipes->outfd, 1);
		if (pipes->next->next)
			close(pipes->next->infd);
		exec_cmd(vars, pipes->cmd);
		free_pipes(to_free);
		exit_process(vars);
	}
	while (!pipes->next->next && wait(&g_exit) > 0)
		continue ;
	if (pipes->outfd != 1)
		close(pipes->outfd);
	if (g_exit >= 255)
		g_exit /= 256;
}

void	check_heredoc(t_vars *vars, char *str, t_pipes *pipes)
{
	t_cmd	*cmd;
	t_redir	*tmp;

	cmd = parse_cmd(vars, str);
	if (cmd && cmd->redirs)
	{
		tmp = cmd->redirs;
		while (cmd->redirs->next)
		{
			if (!ft_strncmp(cmd->redirs->type, "HEREDOC", 8))
				exec_heredoc(vars, cmd, pipes);
			cmd->redirs = cmd->redirs->next;
		}
		cmd->redirs = tmp;
	}
	if (cmd)
		free_cmd(cmd);
}

void	pipe_loop(t_vars *vars, char *input)
{
	char	**cmds;
	t_pipes	*pipes;
	t_pipes *tmp;

	cmds = ft_split_pipes(input);
	if (!cmds[0] || input[0] == '|')
	{
		g_exit = 2;
		return (ft_putstr_fd("minishell: syntax error\n", 2));
	}	
	signal(SIGINT, ctrl_c_pipe_handler);
	pipes = parse_pipes(cmds);
	if (!pipes)
		return (ft_putstr_fd("Malloc failed\n", 2),
			close_minishell(vars, NULL));
	if (!pipes->next)
	{
		check_heredoc(vars, pipes->cmd, pipes);
		exec_cmd(vars, pipes->cmd);
		free_pipes(pipes);
		return ;
	}
	tmp = pipes;
	while (pipes->next)
	{
		check_heredoc(vars, pipes->cmd, tmp);
		exec_pipes(vars, pipes, tmp);
		if (pipes->infd != 0)
			close(pipes->infd);
		pipes = pipes->next;
	}
	free_pipes(tmp);
}
