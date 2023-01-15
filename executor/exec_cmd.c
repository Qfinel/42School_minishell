/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:57:00 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/15 13:01:04 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	change_fd(t_redir *redir)
{
	int	fd;

	if (!ft_strncmp(redir->type, "OUTPUT", 7))
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!ft_strncmp(redir->type, "APPEND", 7))
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (!ft_strncmp(redir->type, "APPEND", 7)
		|| !ft_strncmp(redir->type, "OUTPUT", 7))
		dup2(fd, 1);
	if (!ft_strncmp(redir->type, "INPUT", 6))
	{
		fd = open(redir->filename, O_RDONLY);
		dup2(fd, 0);
	}
	if (ft_strncmp(redir->type, "HEREDOC", 8) && fd < 0)
		return ((void)printf("minishell: err: invalid filename: %s\n",
				redir->filename), 1);
	if (!ft_strncmp(redir->type, "HEREDOC", 8))
	{
		fd = open("executor/heredoc.tmp", O_RDONLY);
		dup2(fd, 0);
	}
	return (0);
}

static void	do_redirections(t_vars *vars, t_cmd *cmd, t_pipes *pipes)
{
	int	id;

	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (cmd->redirs->next)
		{
			if (change_fd(cmd->redirs) > 0)
			{
				g_exit = 1;
				free_cmd(cmd);
				free_pipes(pipes);
				exit_process(vars);
			}
			cmd->redirs = cmd->redirs->next;
		}
		if (is_builtin(vars, cmd))
			exit(g_exit);
		else
			execve(cmd->command, cmd->args, vars->envp);
	}
	wait(&g_exit);
}

static void	run_command(t_cmd *cmd, t_vars *vars, t_pipes *pipes)
{
	int	id;

	if (!cmd->redirs)
	{
		if (!is_builtin(vars, cmd))
		{
			id = fork();
			if (id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				execve(cmd->command, cmd->args, vars->envp);
			}
			wait(&g_exit);
		}
	}
	else
		do_redirections(vars, cmd, pipes);
}

void	check_command(char *arg)
{
	struct stat	stats;

	stat(arg, &stats);
	if (S_ISDIR(stats.st_mode) && arg[0] != '.')
	{
		printf("minishell: %s: is a directory\n", arg);
		g_exit = 126;
	}
	else
	{
		printf("minishell: %s: command not found\n", arg);
		g_exit = 127;
	}
}

void	exec_cmd(t_vars *vars, char *input, t_pipes *pipes)
{
	t_cmd		*cmd;

	cmd = parse_cmd(vars, input);
	show_signals();
	if (!cmd)
	{
		g_exit = 2;
		return ((void)printf("minishell: parsing error\n"));
	}
	if (cmd->command)
		run_command(cmd, vars, pipes);
	else
		check_command(cmd->args[0]);
	if (g_exit >= 255)
		g_exit /= 256;
	else if (g_exit == 2)
		g_exit = 130;
	free_cmd(cmd);
}
