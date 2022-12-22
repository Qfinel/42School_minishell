/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:56:13 by sdukic            #+#    #+#             */
/*   Updated: 2022/12/21 18:15:51 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_words_with_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] != '"' && str[i])
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'' && str[i])
				i++;
		}
		else if (str[i] == '$')
		{
			i++;
			while (str[i] != ' ' && str[i])
				i++;
		}
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

char	**split_with_quotes(char *str)
{
	char	**result;
	char	*tmp;
	int		i;
	int		j;
	int test;


	// str = remove_unclosed_quotes(str);
	test = count_words_with_quotes(str);

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (count_words_with_quotes(str) + 1));
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			tmp = ft_substr(str, i, ft_strlen(str));
			result[j] = ft_substr(tmp, 0, ft_strchr(tmp, '"') - tmp);
			if (tmp)
			free(tmp);
			j++;
			i += ft_strlen(result[j - 1]) + 1;
		}
		else if (str[i] == '\'')
		{
			i++;
			tmp = ft_substr(str, i, ft_strlen(str));
			result[j] = ft_substr(tmp, 0, ft_strchr(tmp, '\'') - tmp);
			free(tmp);
			j++;
			i += ft_strlen(result[j - 1]) + 1;
		}
		else if (str[i] == '$')
		{
			i++;
			tmp = ft_substr(str, i, ft_strlen(str));
			result[j] = ft_substr(tmp, 0, ft_strchr(tmp, ' ') - tmp);
			free(tmp);
			j++;
			i += ft_strlen(result[j - 1]);
		}
		else
		{
			tmp = ft_substr(str, i, ft_strlen(str));
			result[j] = ft_substr(tmp, 0, ft_strchr(tmp, ' ') - tmp);
			free(tmp);
			j++;
			i += ft_strlen(result[j - 1]);
		}
		if (str[i] == ' ')
			i++;
	}
	result[j] = NULL;
	return (result);
}
