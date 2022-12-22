/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:12:04 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/22 16:21:04 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_strings(char **strings)
{
	int	i;

	i = 0;
	while (strings[i])
	{
		free(strings[i]);
		i++;
	}
	free(strings);
}

void	free_redirs(t_redir *redir)
{
	while (redir->next)
	{
		free(redir->filename);
		free(redir);
		redir = redir->next;
	}
	free(redir);
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
