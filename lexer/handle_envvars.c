/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:45:23 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/09 18:37:36 by sdukic           ###   ########.fr       */
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
	result = ft_calloc(sizeof(char *),
			(count_words_starting_with_dollar(str) + 1));
	while (str[i] && result)
	{
		if (str[i] == '$' && !is_envvar_in_single_quotes(str, i)
			&& str[i + 1] && str[i + 1] != ' ' && str[i + 1]
			!= '"' && str[i + 1] != 0)
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
	return (result);
}

int	check_envvars(char **envvars)
{
	if (!envvars || !envvars[0])
	{
		if (envvars)
			free(envvars);
		return (0);
	}
	return (1);
}

char	*replace_single_envvar(t_vars vars, char *input, char *envvar)
{
	char	*env_value;
	char	*temp;

	temp = input;
	env_value = get_env_value(&vars, envvar + 1);
	if (env_value)
		input = ft_str_replace(input, envvar, env_value);
	else
		input = ft_str_replace(input, envvar, "");
	if (env_value)
		free(env_value);
	free(temp);
	return (input);
}

char	*replace_envvar_with_value(t_vars vars, char *input)
{
	int		i;
	char	**envvars;

	if (input == NULL || !ft_strchr(input, '$'))
		return (input);
	envvars = get_words_starting_with_dollar(input);
	if (!check_envvars(envvars))
		return (input);
	i = 0;
	while (envvars[i])
	{
		input = replace_single_envvar(vars, input, envvars[i]);
		i++;
	}
	free_strings(envvars);
	return (input);
}
