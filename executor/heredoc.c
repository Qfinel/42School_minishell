/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:09:21 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/15 15:54:17 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_to_tmp(char *input)
{
	int	fd;

	fd = open("executor/heredoc.tmp", O_WRONLY | O_CREAT | O_APPEND, 0644);
	write(fd, input, ft_strlen(input));
	write(fd, "\n", 1);
	close(fd);
}

void	truncate_tmp(void)
{
	int	fd;

	fd = open("executor/heredoc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd != -1)
		close(fd);
}

void	delete_tmp(t_vars *vars)
{
	if (!access("executor/heredoc.tmp", F_OK))
		exec_cmd(vars, "rm executor/heredoc.tmp", NULL);
}

void	exec_heredoc(t_vars *vars, t_cmd *cmd, t_pipes *pipes, t_redir *head)
{
	char	*input;

	truncate_tmp();
	if (fork() == 0)
	{
		signal(SIGINT, SIG_DFL);
		while (1)
		{
			input = readline("> ");
			if (!ft_strncmp(input, cmd->redirs->filename,
					ft_strlen(cmd->redirs->filename) + 1))
				break ;
			if (!cmd->args[1])
				add_to_tmp(input);
			free(input);
		}
		free(input);
		g_exit = 0;
		cmd->redirs = head;
		free_cmd(cmd);
		free_pipes(pipes);
		exit_process(vars);
	}
	wait(&g_exit);
}
