/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:57:00 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/21 17:38:28 by jtsizik          ###   ########.fr       */
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

	while (cmd->redirs->next)
	{
		id = fork();
		if (id == 0)
		{
			change_fd(cmd->redirs);
			if (!is_builtin(vars, cmd))
					execve(cmd->command, cmd->args, vars->envp);
		}
		cmd->redirs = cmd->redirs->next;
	}
}

void	exec_cmd(t_vars *vars, char *input)
{
	t_cmd	*cmd;
	int		id;

	cmd = parse_cmd(vars, input);
	if (!cmd)
		return ((void)printf("minishell: parsing error\n"));
	if (cmd->command)
	{
		if (!cmd->redirs)
		{
			id = fork();
			if (id == 0)
			{
				if (!is_builtin(vars, cmd))
					execve(cmd->command, cmd->args, vars->envp);
			}
			wait(NULL);
		}
		else
			do_redirections(vars, cmd);
		wait(NULL);
	}
	else
		printf("minishell: command not found: '%s'\n", cmd->args[0]);
	free_cmd(cmd);
}
