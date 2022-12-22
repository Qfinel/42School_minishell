/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:00:54 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/22 17:15:06 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;

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

int	redirections_exist(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

char	**get_clean_args(char *input, t_redir *redir)
{
	char	**args;
	char	**tmp;
	t_redir	**head;
	int		i;
	int		j;

	i = 0;
	j = 0;
	head = malloc(sizeof(t_redir *));
	*head = redir;
	tmp = ft_split_charset(input, " ><");
	if (!tmp[1])
		return (NULL);
	args = ft_calloc(ft_arr_len(tmp), sizeof(char *));
	while (tmp[i])
	{
		while (redir->next)
		{
			if (!ft_strncmp(tmp[i], redir->filename, ft_strlen(tmp[i]) + 1))
				i++;
			redir = redir->next;
		}
		redir = *head;
		if (tmp[i])
			args[j] = ft_strdup(tmp[i]);
		j++;
		if (tmp[i])
			i++;
	}
	free(head);
	free_strings(tmp);
	return (args);
}

t_cmd	*parse_cmd(t_vars *vars, char *input)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (redirections_exist(input))
		cmd->redirs = parse_redirections(input);
	else
		cmd->redirs = NULL;
	if (!cmd->redirs && redirections_exist(input))
		return (NULL);
	if (!cmd->redirs)
		cmd->args = split_with_quotes(input);
	else
		cmd->args = get_clean_args(input, cmd->redirs);
	if (!cmd->args)
		return (NULL);
	if (cmd->args[0][0] == '/')
	{
		if (access(cmd->args[0], F_OK) == 0)
			cmd->command = ft_strdup(cmd->args[0]);
		else
			cmd->command = NULL;
	}
	else if (!ft_strncmp(cmd->args[0], "export", 7) || !ft_strncmp(cmd->args[0], "unset", 6))
		cmd->command = ft_strdup(cmd->args[0]);
	else
		cmd->command = get_cmd(vars->paths, cmd->args[0]);
	return (cmd);
}
