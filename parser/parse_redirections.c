/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:21:17 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/21 13:19:36 by jtsizik          ###   ########.fr       */
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
	filename = ft_strdup(tmp[0]);
	free_strings(tmp);
	return (filename);
}

t_redir	*parse_redirections(char *input)
{
	t_redir	*redir;
	t_redir	**head;
	int		i;

	i = 0;
	head = malloc (sizeof(t_redir *));
	redir = malloc(sizeof(t_redir));
	*head = redir;
	while (input[i + 1])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			redir->type = get_redir_type(&input[i]);
			redir->filename = get_redir_filename(&input[i]);
			if (!redir->filename)
				return (NULL);
			redir->next = malloc(sizeof(t_redir));
			redir = redir->next;
		}
		i++;
	}
	redir = *head;
	return (redir);
}
