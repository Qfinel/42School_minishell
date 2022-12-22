/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:45:23 by sdukic            #+#    #+#             */
/*   Updated: 2022/12/22 17:38:48 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_env_value(t_vars *vars, char *key)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (vars->envp[i])
	{
		if (!ft_strncmp(vars->envp[i], key, ft_strlen(key)))
		{
			result = ft_substr(vars->envp[i], ft_strlen(key) + 1, ft_strlen(vars->envp[i]));
			break ;
		}
		i++;
	}
	return (result);
}

char	*ft_str_replace(char *str, char *old, char *new)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_strdup(str);
	while (str[i])
	{
		if (!ft_strncmp(&result[i], old, ft_strlen(old)))
		{
			result = ft_strjoin(ft_substr(result, 0, i), new);
			result = ft_strjoin(result, ft_substr(str, i + ft_strlen(old), ft_strlen(str)));
		}
		i++;
	}
	return(result);
}

int count_words_starting_with_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
			count++;
		i++;
	}
	return (count);
}

char	*get_end_of_envvar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '"')
			break ;
		i++;
	}

	return (str + i);
}

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

static char **get_words_starting_with_dollar(char *str)
{
	char	**result;
	char	*temp_str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc(sizeof(char *) * (count_words_starting_with_dollar(str) + 1));
	while (str[i])
	{
		if (str[i] == '$' && !is_envvar_in_single_quotes(str, i))
		{
			// temp_str = ft_strchr(&str[i], ' ');
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
	if (!envvars)
		return (input);
	i = 0;
	while (envvars[i])
	{
		env_value = get_env_value(&vars, envvars[i] + 1);
		if (env_value)
		{
			input = ft_str_replace(input, envvars[i], env_value);
		}
		else
		{
			input = ft_str_replace(input, envvars[i], "");
		}
		i++;
	}
	free_strings(envvars);
	return (input);
}
