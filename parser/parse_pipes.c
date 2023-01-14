/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:01:11 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 17:15:50 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parsing_loop(char **cmds, t_pipes *pipes, int *end)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(end + i * 2) < 0)
				return (printf("pipe error\n"), -1);
		}
		pipes->next = ft_calloc(1, sizeof(t_pipes));
		if (i == 0)
			pipes->infd = 0;
		else
			pipes->infd = end[(i - 1) * 2];
		if (cmds[i + 1])
			pipes->outfd = end[i * 2 + 1];
		else
			pipes->outfd = 1;
		pipes->cmd = ft_strdup(cmds[i]);
		pipes = pipes->next;
		i++;
	}
	return (0);
}

t_pipes	*parse_pipes(char **cmds)
{
	t_pipes	*pipes;
	t_pipes	*head;
	int		*end;

	pipes = ft_calloc(1, sizeof(t_pipes));
	end = ft_calloc((ft_arr_len(cmds) - 1) * 2 + 1, sizeof(int));
	if (!pipes || !end)
		return (NULL);
	if (!cmds[1])
	{
		pipes->cmd = ft_strdup(cmds[0]);
		pipes->next = NULL;
		free(end);
		free_strings(cmds);
		return (pipes);
	}
	head = pipes;
	if (parsing_loop(cmds, pipes, end) < 0)
		return (NULL);
	free(end);
	free_strings(cmds);
	return (head);
}
