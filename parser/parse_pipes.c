/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 13:01:11 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/12 15:23:14 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_pipes	*parse_pipes(char **cmds)
{
	t_pipes	*pipes;
	t_pipes *head;
	int		*end;
	int		i;

	i = 0;
	pipes = ft_calloc(1, sizeof(t_pipes));
	end = ft_calloc((ft_arr_len(cmds) - 1) * 2 + 1, sizeof(int));
	if (!pipes || !end)
		return (NULL);
	head = pipes;
	while (cmds[i])
	{
		if (cmds[i + 1])
		{
			if (pipe(end + i * 2) < 0)
				return (printf("pipe error\n"), NULL);
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
	pipes = head;
	free(end);
	free_strings(cmds);
	return (pipes);
}