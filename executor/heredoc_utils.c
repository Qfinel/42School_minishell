/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:09:21 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/11 14:49:00 by jtsizik          ###   ########.fr       */
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

	fd = open("executor/heredoc.tmp", O_WRONLY | O_TRUNC, 0644);
	if (fd != -1)
		close(fd);
}

void	delete_tmp(t_vars *vars)
{
	if (!access("executor/heredoc.tmp", F_OK))
		exec_cmd(vars, "rm executor/heredoc.tmp");
}
