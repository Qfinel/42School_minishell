/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:21:17 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/24 12:04:37 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_redir_type(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return ("APPEND");
	if (str[0] == '>' && str[1] != '>')
		return ("OUTPUT");
	if (str[0] == '<' && str[1] == '<')
		return ("HEREDOC");
	if (str[0] == '<' && str[1] != '<')
		return ("INPUT");
	else
		return (NULL);
}

char	*get_redir_filename(char *str)
{
	int		i;
	char	**tmp;
	char	*filename;

	i = 0;
	while (str[i] == '>' || str[i] == '<')
		i++;
	tmp = ft_split(&str[i], ' ');
	if (tmp[0])
		filename = ft_strdup(tmp[0]);
	else
		return (NULL);
	if (tmp[0])
		free_strings(tmp);
	return (filename);
}

t_redir	*parse_redirections(char *input)
{
	t_redir	*redir;
	t_redir	**head;
	int		i;

	i = 0;
	head = malloc(sizeof(t_redir *));
	redir = ft_calloc(1, sizeof(t_redir));
	*head = redir;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			redir->type = get_redir_type(&input[i]);
			redir->filename = get_redir_filename(&input[i]);
			if (!redir->filename || i == 0)
				return (NULL);
			redir->next = ft_calloc(1, sizeof(t_redir));
			redir = redir->next;
			if (input[i + 1] == '>' || input[i + 1] == '<')
				i++;
		}
		i++;
	}
	redir = *head;
	free(head);
	return (redir);
}
