/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:45:23 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/02 16:26:34 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_envvar_in_single_quotes(char *str, int index)
{
	int		i;
	int		quotes_open;

	i = 0;
	quotes_open = 0;
	while (str[i] && i < index)
	{
		if (str[i] == '\'')
			quotes_open = !quotes_open;
		i++;
	}
	if (quotes_open)
		return (1);
	else
		return (0);
}

static char	**get_words_starting_with_dollar(char *str)
{
	char	**result;
	char	*temp_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *)
			* (count_words_starting_with_dollar(str) + 1));
	while (str[i])
	{
		if (str[i] == '$' && !is_envvar_in_single_quotes(str, i)
			&& str[i + 1] && str[i + 1] != ' ')
		{
			temp_str = get_end_of_envvar(&str[i]);
			if (temp_str)
				result[j] = ft_substr(&str[i], 0, temp_str - &str[i]);
			else
				result[j] = ft_strdup(&str[i]);
			j++;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

char	*replace_envvar_with_value(t_vars vars, char *input)
{
	int		i;
	char	**envvars;
	char	*env_value;

	if (input == NULL || !ft_strchr(input, '$'))
		return (input);
	envvars = get_words_starting_with_dollar(input);
	if (!envvars || !envvars[0])
		return (input);
	i = 0;
	while (envvars[i])
	{
		env_value = get_env_value(&vars, envvars[i] + 1);
		if (env_value)
			input = ft_str_replace(input, envvars[i], env_value);
		else
			input = ft_str_replace(input, envvars[i], "");
		i++;
	}
	free_strings(envvars);
	free(env_value);
	return (input);
}
