/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 12:21:17 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 15:07:41 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_redir_type(char *str)
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

static char	*get_redir_filename(char *str)
{
	int		i;
	char	**tmp;
	char	*filename;

	i = 0;
	while (str[i] == '>' || str[i] == '<')
		i++;
	tmp = split_with_quotes(&str[i]);
	if (!tmp)
		tmp = ft_split(&str[i], ' ');
	if (tmp[0])
		filename = ft_strdup(tmp[0]);
	else
		return (NULL);
	if (tmp[0])
		free_strings(tmp);
	return (filename);
}

static t_redir	*get_redir(t_redir *redir, char *input, int i)
{
	redir->type = get_redir_type(&input[i]);
	redir->filename = get_redir_filename(&input[i]);
	if (!redir->filename)
		return (NULL);
	redir->next = ft_calloc(1, sizeof(t_redir));
	if (!redir->next)
		return (NULL);
	redir = redir->next;
	return (redir);
}

t_redir	*parse_redirections(char *input)
{
	t_redir	*redir;
	t_redir	*tmp;
	int		i;

	i = 0;
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	tmp = redir;
	while (input[i])
	{
		if ((input[i] == '>' || input[i] == '<') && is_real(input, i))
		{
			redir = get_redir(redir, input, i);
			if (!redir)
				return (NULL);
			if (input[i + 1] == '>' || input[i + 1] == '<')
				i++;
		}
		i++;
	}
	redir = tmp;
	return (redir);
}
