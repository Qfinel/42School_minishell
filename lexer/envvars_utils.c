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

char	*get_env_value(t_vars *vars, char *key)
{
	int		i;
	char	*result;

	i = 0;
	result = NULL;
	while (vars->envp[i])
	{
		if (!ft_strncmp(vars->envp[i], key, ft_strlen(key)))
		{
			result = ft_substr(vars->envp[i], ft_strlen(key) + 1,
					ft_strlen(vars->envp[i]));
			break ;
		}
		i++;
	}
	if (key[0] == '?' && !key[1])
		result = ft_itoa(g_exit);
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
			result = ft_strjoin(result, ft_substr(str,
						i + ft_strlen(old), ft_strlen(str)));
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
