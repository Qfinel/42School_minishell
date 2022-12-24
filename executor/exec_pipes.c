/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 11:55:43 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/24 11:14:47 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exec_pipes(t_vars *vars, char *input)
{
	char	**cmds;
	int		end[2];
	int		i;
	int		id;
	int		tmp_fd;

	i = 0;
	tmp_fd = 0;
	cmds = ft_split(input, '|');
	signal(SIGINT, ctrl_c_pipe_handler);
	while (cmds[i])
	{
		pipe(end);
		id = fork();
		if (id == 0)
		{
			dup2(tmp_fd, 0);
			if (cmds[i + 1])
				dup2(end[1], 1);
			close(end[0]);
			exec_cmd(vars, cmds[i]);
			free_strings(cmds);
			exit_process(vars);
		}
		if (!cmds[i + 1])
			wait(NULL);
		close(end[1]);
		tmp_fd = end[0];
		i++;
	}
	close(end[0]);
	free_strings(cmds);
}
