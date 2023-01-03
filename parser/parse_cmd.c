/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:00:54 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/03 16:01:56 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_input_redirs(char *str)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if ((str[i] != '>' && str[i] != '<') || !is_real_redir(str, i))
			newstr[i] = str[i];
		else
			newstr[i] = ' ';
		i++;
	}
	return (newstr);
}

static void	clean_args_loop(t_redir	**head, t_redir *redir,
	char **tmp, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
}

char	**get_clean_args(char *input, t_redir *redir)
{
	char	**args;
	char	**tmp;
	char	*str;
	t_redir	**head;

	head = malloc(sizeof(t_redir *));
	*head = redir;
	str = remove_input_redirs(input);
	tmp = split_with_quotes(str);
	if (!tmp[1])
		return (NULL);
	args = ft_calloc(ft_arr_len(tmp), sizeof(char *));
	clean_args_loop(head, redir, tmp, args);
	free(head);
	free_strings(tmp);
	free(str);
	return (args);
}

t_cmd	*parse_cmd(t_vars *vars, char *input)
{
	t_cmd	*cmd;
	char	*trimmed;

	cmd = malloc(sizeof(t_cmd));
	trimmed = ft_strtrim(input, " ");
	if (redirections_exist(input))
		cmd->redirs = parse_redirections(input);
	else
		cmd->redirs = NULL;
	if (!cmd->redirs && redirections_exist(input))
		return (NULL);
	if (!cmd->redirs)
		cmd->args = split_with_quotes(trimmed);
	else
		cmd->args = get_clean_args(trimmed, cmd->redirs);
	free(trimmed);
	if (!cmd->args)
		return (NULL);
	get_command(cmd, vars);
	return (cmd);
}
