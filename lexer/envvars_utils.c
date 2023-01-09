/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envvars_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:45:23 by sdukic            #+#    #+#             */
/*   Updated: 2023/01/09 15:23:04 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_word_before_equal_sign(char *str)
{
	int		i;
	char	*result;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	result = ft_substr(str, 0, i);
	return (result);
}

int	does_envvar_exitst(t_vars *vars, char *envvar)
{
	int		i;
	char	*temp_str;

	i = 0;
	while (vars->envp[i])
	{
		temp_str = get_word_before_equal_sign(vars->envp[i]);
		if (!ft_strncmp(temp_str, envvar, ft_strlen(envvar))
			&& ft_strlen(temp_str) == ft_strlen(envvar))
		{
			free(temp_str);
			return (1);
		}
		free(temp_str);
		i++;
	}
	if (!ft_strncmp(envvar, "?", 2))
		return (1);
	return (0);
}

char	*get_env_value(t_vars *vars, char *key)
{
	int		i;
	char	*result;
	char	*old_result;

	if (does_envvar_exitst(vars, key) == 0)
		return (NULL);
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
	if (key[0] == '?' && (!key[1] || key[1] == ' '))
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
			break ;
		}
		i++;
	}
	return (result);
}
