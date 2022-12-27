/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:57:00 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/27 13:13:39 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_heredoc(t_redir *redir)
{
	char	*input;

	while (1)
	{
		input = readline("heredoc> ");
		if (!ft_strncmp(input, redir->filename, ft_strlen(redir->filename) + 1))
			break ;
	}
}

void	change_fd(t_redir *redir)
{
	int	fd;

	if (!ft_strncmp(redir->type, "OUTPUT", 7))
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
			printf("minishell: err: invalid filename: %s\n", redir->filename);
		dup2(fd, 1);
	}
	if (!ft_strncmp(redir->type, "APPEND", 7))
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
			printf("minishell: err: invalid filename: %s\n", redir->filename);
		dup2(fd, 1);
	}
	if (!ft_strncmp(redir->type, "INPUT", 6))
	{
		fd = open(redir->filename, O_RDONLY);
		if (fd < 0)
			printf("minishell: err: invalid filename: %s\n", redir->filename);
		dup2(fd, 0);
	}
	if (!ft_strncmp(redir->type, "HEREDOC", 8))
		exec_heredoc(redir);
}

void	do_redirections(t_vars *vars, t_cmd *cmd)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		while (cmd->redirs->next)
		{
			change_fd(cmd->redirs);
			cmd->redirs = cmd->redirs->next;
		}
		if (is_builtin(vars, cmd))
			exit(0);
		else
			execve(cmd->command, cmd->args, vars->envp);
	}
}

void	exec_cmd(t_vars *vars, char *input)
{
	t_cmd	*cmd;
	int		id;

	cmd = parse_cmd(vars, input);
	signal(SIGINT, ctrl_c_pipe_handler);
	if (!cmd)
	{
		exit_status = 1;
		return ((void)printf("minishell: parsing error\n"));
	}
	if (cmd->command)
	{
		if (!cmd->redirs)
		{
			if (!is_builtin(vars, cmd))
			{
				id = fork();
				if (id == 0)
						execve(cmd->command, cmd->args, vars->envp);
				wait(&exit_status);
			}
		}
		else
			do_redirections(vars, cmd);
		wait(&exit_status);
		exit_status /= 256;
	}
	else
	{
		printf("minishell: command not found: '%s'\n", cmd->args[0]);
		exit_status = 127;
	}
	free_cmd(cmd);
}
