/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:21:31 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 22:09:31 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c_handler(int sig)
{
	(void)sig;
	g_exit = 1;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ctrl_c_pipe_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	close_minishell(t_vars *vars, char *input)
{
	printf("exit\n");
	if (input)
		check_exit(input);
	if (vars->paths)
		free_strings(vars->paths);
	if (input)
		free(input);
	if (vars->envp)
		free_strings(vars->envp);
	exit(g_exit);
}

void	hide_ctrl_c(void)
{
	pid_t	pid;
	int		status;
	char	*args[3];

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		exit(1);
	}
	if (pid == 0)
	{
		args[0] = "stty";
		args[1] = "-echoctl";
		args[2] = NULL;
		execv("/bin/stty", args);
	}
	else
	{
		waitpid(pid, &status, 0);
	}
}
