/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:56:13 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/08 16:23:09 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_with_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
			i += skip_to_next('"', str);
		else if (str[i] == '\'')
			i += skip_to_next('\'', str);
		else if (str[i] == '$')
			i += skip_to_next(' ', str);
		else if (str[i] != ' ')
		{
			while (str[i] != ' ' && str[i])
				i++;
		}
		if (str[i] == ' ')
			i++;
		count++;
	}
	return (count);
}

char	*remove_unclosed_quotes(char *str)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	if (quote % 2 != 0)
	{
		while (str[j])
		{
			if (str[j] == '"')
				ft_memmove(&str[j], &str[j + 1], ft_strlen(str) - j);
			j++;
		}
	}
	return (str);
}

void	split_segment(char *str, char **result, t_vector *iter, char c)
{
	char	*tmp;

	(iter->i)++;
	tmp = ft_substr(str, iter->i, ft_strlen(str));
	result[iter->j] = ft_substr(tmp, 0, ft_strchr(tmp, c) - tmp);
	if (tmp)
		free(tmp);
	(iter->j)++;
	iter->i += ft_strlen(result[iter->j - 1]) + 1;
}

void	split_last_segment(char *str, char **result, t_vector *iter)
{
	char	*tmp;

	tmp = ft_substr(str, iter->i, ft_strlen(str));
	result[iter->j] = ft_substr(tmp, 0, ft_strchr(tmp, ' ') - tmp);
	if (tmp)
		free(tmp);
	(iter->j)++;
	iter->i += ft_strlen(result[iter->j - 1]);
}

char	**split_with_quotes(char *str)
{
	char		**result;
	t_vector	iter;

	iter.i = 0;
	iter.j = 0;
	while (str[iter.i] == ' ')
		iter.i++;
	result = ft_calloc(sizeof(char *), count_words_with_quotes(str) + 1);
	if (!result || !str[0])
		return (NULL);
	while (str[iter.i])
	{
		if (str[iter.i] == '"')
			split_segment(str, result, &iter, '"');
		else if (str[iter.i] == '\'')
			split_segment(str, result, &iter, '\'');
		else if (str[iter.i] == '$' && str[iter.i + 1] != ' '
			&& str[iter.i + 1])
			split_segment(str, result, &iter, ' ');
		else
			split_last_segment(str, result, &iter);
		while (str[iter.i] == ' ')
			iter.i++;
	}
	return (result);
}
