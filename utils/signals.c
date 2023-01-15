/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:21:31 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/15 13:03:32 by jtsizik          ###   ########.fr       */
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

void	hide_signals(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSAFLUSH, &tty);
}

void	show_signals(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag |= ECHOCTL;
	tcsetattr(0, TCSAFLUSH, &tty);
}
