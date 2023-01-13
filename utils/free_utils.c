/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:12:04 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/13 16:55:48 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		if (strings[i])
			free(strings[i]);
		i++;
	}
	if (strings)
		free(strings);
}

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->filename);
		free(tmp);
	}
}

void	free_pipes(t_pipes *pipes)
{
	t_pipes	*tmp;

	while (pipes)
	{
		tmp = pipes;
		pipes = pipes->next;
		free(tmp->cmd);
		if (tmp->infd != 0)
			close(tmp->infd);
		free(tmp);
	}
}

void	free_cmd(t_cmd *cmd)
{
	if (cmd->command)
		free(cmd->command);
	if (cmd->args)
		free_strings(cmd->args);
	if (cmd->redirs)
		free_redirs(cmd->redirs);
	free(cmd);
}
