/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:35:38 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 17:19:11 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	add_var(t_vars *vars, char *name, char *val)
{
	int		i;
	char	**new_envp;

	i = 0;
	new_envp = ft_calloc(ft_arr_len(vars->envp) + 2, sizeof(char *));
	if (!new_envp)
		return ;
	while (vars->envp[i])
	{
		new_envp[i] = ft_strdup(vars->envp[i]);
		i++;
	}
	new_envp[i] = ft_strjoin(name, val);
	free_strings(vars->envp);
	vars->envp = new_envp;
}

void	change_oldpwd(t_vars *vars)
{
	int		i;
	char	*tmp;

	i = 0;
	while (vars->envp[i])
	{
		if (!ft_strncmp(vars->envp[i], "OLDPWD=", 7))
			break ;
		i++;
	}
	tmp = getcwd(NULL, 0);
	if (vars->envp[i])
	{
		free(vars->envp[i]);
		vars->envp[i] = ft_strjoin("OLDPWD=", tmp);
	}
	else
		add_var(vars, "OLDPWD=", tmp);
	free(tmp);
}

void	change_pwd(t_vars *vars)
{
	int		i;
	char	*tmp;

	i = 0;
	while (vars->envp[i])
	{
		if (!ft_strncmp(vars->envp[i], "PWD=", 4))
			break ;
		i++;
	}
	tmp = getcwd(NULL, 0);
	if (vars->envp[i])
	{
		free(vars->envp[i]);
		vars->envp[i] = ft_strjoin("PWD=", tmp);
	}
	else
		add_var(vars, "PWD=", tmp);
	free(tmp);
}

int	only_slashes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '/')
			return (0);
		i++;
	}
	return (1);
}
