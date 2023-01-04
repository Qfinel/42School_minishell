/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:45:23 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/04 17:04:49 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_vars *vars, char *key)
{
	int		i;
	char	*result;
	char	*old_result;

	i = 0;
	result = NULL;
	old_result = NULL;
	while (vars->envp[i])
	{
		if (!ft_strncmp(vars->envp[i], key, ft_strlen(key)))
		{
			if (old_result)
				free(old_result);
			result = ft_substr(vars->envp[i], ft_strlen(key) + 1,
					ft_strlen(vars->envp[i]));
			old_result = result;
			break ;
		}
		i++;
	}
	if (key[0] == '?' && !key[1])
		result = ft_itoa(g_exit);
	return (result);
}

void	free_two(char *str1, char *str2)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

char	*ft_str_replace(char *str, char *old, char *new)
{
	char	*old_result;
	int		i;
	char	*result;
	char	*sub_str;

	i = 0;
	result = ft_strdup(str);
	while (str[i])
	{
		if (!ft_strncmp(&result[i], old, ft_strlen(old)))
		{
			old_result = result;
			sub_str = ft_substr(result, 0, i);
			result = ft_strjoin(sub_str, new);
			free_two(sub_str, old_result);
			old_result = result;
			sub_str = ft_substr(str, i + ft_strlen(old), ft_strlen(str));
			result = ft_strjoin(result, sub_str);
			free_two(sub_str, old_result);
		}
		i++;
	}
	return (result);
}

int	count_words_starting_with_dollar(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1])
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
		if (str[i] == ' ' || str[i] == '|' || str[i] == '"')
			break ;
		i++;
	}
	return (str + i);
}
