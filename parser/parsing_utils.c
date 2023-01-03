/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:39:31 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/03 16:28:21 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd_path(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

	if (!paths)
		return (NULL);
	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		paths++;
	}
	return (NULL);
}

void	get_command(t_cmd *cmd, t_vars *vars)
{
	if (cmd->args[0][0] == '/')
	{
		if (access(cmd->args[0], F_OK) == 0)
			cmd->command = ft_strdup(cmd->args[0]);
		else
			cmd->command = NULL;
	}
	else if (!ft_strncmp(cmd->args[0], "export", 7)
		|| !ft_strncmp(cmd->args[0], "unset", 6))
		cmd->command = ft_strdup(cmd->args[0]);
	else
		cmd->command = get_cmd_path(vars->paths, cmd->args[0]);
}

int	is_real_redir(char *input, int i)
{
	int	j;
	int	quotes1;
	int	quotes2;

	j = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (j < i)
	{
		if (input[j] == '\'' || input[j] == '\"')
			quotes1++;
		j++;
	}
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			quotes2++;
		i++;
	}
	if (quotes1 % 2 > 0 && quotes2 > 0)
		return (0);
	else
		return (1);
}

int	redirections_exist(char *input)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (input[i])
	{
		if ((input[i] == '>' || input[i] == '<') && is_real_redir(input, i))
			counter++;
		i++;
	}
	return (counter);
}
