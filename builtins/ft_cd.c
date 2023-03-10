/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 17:25:24 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 17:21:47 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	cd_home(t_vars *vars)
{
	char	*tmp;

	tmp = get_env_value(vars, "HOME");
	if (!tmp)
	{
		g_exit = 1;
		printf("minishell: cd: HOME not set\n");
		return ;
	}
	change_oldpwd(vars);
	chdir(tmp);
	free(tmp);
	change_pwd(vars);
	g_exit = 0;
}

static void	cd_back(t_vars *vars)
{
	char	*old_pwd;

	old_pwd = get_env_value(vars, "OLDPWD");
	if (!old_pwd)
	{
		g_exit = 1;
		return ((void)printf("minishell: cd: OLDPWD not set\n"));
	}
	printf("%s\n", old_pwd);
	change_oldpwd(vars);
	chdir(old_pwd);
	free(old_pwd);
	change_pwd(vars);
	g_exit = 0;
}

static void	cd_abs(t_vars *vars, char *path)
{
	struct stat	stats;

	stat(path, &stats);
	if (!S_ISDIR(stats.st_mode))
	{
		g_exit = 1;
		return ((void)printf("minishell: cd: %s: \
		No such file or directory\n", path));
	}
	change_oldpwd(vars);
	g_exit = 0;
	if (only_slashes(path))
		return ((void)chdir("/"), change_pwd(vars));
	chdir(path);
	change_pwd(vars);
}

static void	cd_rel(t_vars *vars, char *path)
{
	struct stat	stats;
	char		*tmp;
	char		*tmp1;
	char		*full_path;

	tmp = getcwd(NULL, 0);
	tmp1 = ft_strjoin(tmp, "/");
	free(tmp);
	full_path = ft_strjoin(tmp1, path);
	free(tmp1);
	stat(full_path, &stats);
	if (!S_ISDIR(stats.st_mode))
	{
		g_exit = 1;
		free(full_path);
		return ((void)printf("minishell: cd: %s: \
		No such file or directory\n", path));
	}
	change_oldpwd(vars);
	g_exit = 0;
	chdir(full_path);
	change_pwd(vars);
	free(full_path);
}

void	ft_cd(t_vars *vars, t_cmd *cmd)
{
	if (!cmd->args[1] || !ft_strncmp(cmd->args[1], "~", 2))
		return (cd_home(vars));
	if (!ft_strncmp(cmd->args[1], "-", 2))
		return (cd_back(vars));
	if (cmd->args[1][0] == '/')
		return (cd_abs(vars, cmd->args[1]));
	else
		return (cd_rel(vars, cmd->args[1]));
}
