/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:09:21 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/09 19:09:32 by jtsizik          ###   ########.fr       */
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
	close(fd);
}
