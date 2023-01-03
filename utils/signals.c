/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:21:31 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/02 16:26:48 by jtsizik          ###   ########.fr       */
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
	g_exit = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}
