/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:57:00 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/07 15:42:17 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_heredoc(t_redir *redir)
{
	char	*input;

	if (!ft_strncmp(redir->type, "HEREDOC", 8))
	{
		while (1)
		{
			input = readline("heredoc> ");
			if (!ft_strncmp(input, redir->filename,
					ft_strlen(redir->filename) + 1))
				break ;
		}
	}
}

static void	change_fd(t_redir *redir)
{
	int	fd;

	if (!ft_strncmp(redir->type, "OUTPUT", 7))
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, 1);
	}
	if (!ft_strncmp(redir->type, "APPEND", 7))
	{
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, 1);
	}
	if (!ft_strncmp(redir->type, "INPUT", 6))
	{
		fd = open(redir->filename, O_RDONLY);
		dup2(fd, 0);
	}
	if (ft_strncmp(redir->type, "HEREDOC", 8) && fd < 0)
		return ((void)printf("minishell: err: invalid filename: %s\n",
				redir->filename), exit(1));
}

static void	do_redirections(t_vars *vars, t_cmd *cmd)
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
			exit(g_exit);
		else
			execve(cmd->command, cmd->args, vars->envp);
	}
	wait(&g_exit);
}

static void	run_command(t_cmd *cmd, t_vars *vars)
{
	int	id;

	signal(SIGINT, ctrl_c_pipe_handler);
	signal(SIGQUIT, backslash_handler);
	if (!cmd->redirs)
	{
		if (!is_builtin(vars, cmd))
		{
			id = fork();
			if (id == 0)
				execve(cmd->command, cmd->args, vars->envp);
			wait(&g_exit);
		}
	}
	else
		do_redirections(vars, cmd);
}

void	exec_cmd(t_vars *vars, char *input)
{
	t_cmd	*cmd;

	cmd = parse_cmd(vars, input);
	if (!cmd)
	{
		g_exit = 1;
		return ((void)printf("minishell: parsing error\n"));
	}
	if (cmd->command)
		run_command(cmd, vars);
	else
	{
		printf("minishell: command not found: '%s'\n", cmd->args[0]);
		g_exit = 127;
	}
	if (g_exit >= 255)
		g_exit /= 256;
	else if (g_exit == 2)
		g_exit = 130;
	free_cmd(cmd);
}
