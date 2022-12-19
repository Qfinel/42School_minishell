/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envvars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:45:23 by sdukic            #+#    #+#             */
/*   Updated: 2022/12/19 14:50:32 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char *ft_str_replace(char *str, char *old, char *new)
{
	char	*result;
	char	*tmp;
	int		i;

	i = 0;
	result = ft_strdup(str);
	while (result[i])
	{
		if (!ft_strncmp(&result[i], old, ft_strlen(old)))
		{
			tmp = result;
			result = ft_strjoin(ft_substr(result, 0, i), new);
			free(tmp);
			tmp = result;
			result = ft_strjoin(result, ft_substr(str, i + ft_strlen(old), ft_strlen(str)));
			free(tmp);
		}
		i++;
	}
	return(result);
}

static int count_words_starting_with_dollar(char *str)
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
		if (str[i] == '$')
		{
			temp_str = ft_strchr(&str[i], ' ');
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

t_vars	replace_envvar_with_value(t_vars vars)
{
	int		i;
	char	**envvars;
	char	*env_value;

	if (vars.input == NULL || !ft_strchr(vars.input, '$'))
		return (vars);
	envvars = get_words_starting_with_dollar(vars.input);
	if (!envvars)
		return (vars);
	i = 0;
	while (envvars[i])
	{
		env_value = get_env_value(&vars, envvars[i] + 1);
		if (env_value)
		{
			vars.input = ft_str_replace(vars.input, envvars[i], get_env_value(&vars, envvars[i] + 1));
		}
		else
		{
			vars.input = ft_str_replace(vars.input, envvars[i], "");
		}
		i++;
	}
	free_strings(envvars);
	return (vars);
}
