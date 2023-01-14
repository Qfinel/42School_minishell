/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:56:13 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/14 16:05:07 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	on_word_end(char **ret, char *word, t_3dvector *vector)
{
	if (vector->j == 0)
	{
		word = malloc(sizeof(char) * 1000);
	}
	word[vector->j] = '\0';
	ret[vector->k] = word;
	vector->k++;
	vector->j = 0;
}

void	init_vars(t_3dvector *vector, char ***ret)
{
	vector->i = 0;
	vector->j = 0;
	vector->k = 0;
	*ret = malloc(sizeof(char *) * 1000);
}

char	**on_unclosed_quote(char **ret, char *word, t_3dvector *vector)
{
	on_word_end(ret, word, vector);
	ret[vector->k] = NULL;
	free_strings(ret);
	return (NULL);
}

char	*on_word_copy(t_3dvector *vector, char *str, char *word)
{
	if (vector->j == 0)
		word = malloc(sizeof(char) * 1000);
	word[vector->j] = str[vector->i];
	vector->j++;
	return (word);
}

char	**split_with_quotes(char *str)
{
	char		quote;
	char		**ret;
	char		*word;
	t_3dvector	vector;

	init_vars(&vector, &ret);
	while (str[vector.i])
	{
		quote = get_opening_quote(quote, str[vector.i]);
		if (quote == 0 && str[vector.i] != ' ' && !is_quote(str[vector.i]))
			word = on_word_copy(&vector, str, word);
		if (quote != 0 && str[vector.i] != quote)
			word = on_word_copy(&vector, str, word);
		if (quote == 0 && (str[vector.i] != ' '
				&& (str[vector.i + 1] == ' ' || str[vector.i + 1] == '\0')))
			on_word_end(ret, word, &vector);
		if (quote != 0 && str[vector.i + 1] == '\0')
			return (on_unclosed_quote(ret, word, &vector));
	vector.i++;
	}
	ret[vector.k] = NULL;
	return (ret);
}
