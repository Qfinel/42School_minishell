/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:36:23 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/17 16:41:32 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd(char **args)
{
	char	*abs_path;
	char	*new_abs_path;

	abs_path = getcwd(NULL, 0);
	if (!args[1])
	{
		abs_path = ft_strjoin("/Users/", getenv("USER"));
		chdir(abs_path);
	}
	else
	{
		if (args[1][0] != '/')
			abs_path = ft_strjoin(abs_path, "/");
		if (!ft_strncmp(args[1], "~", 1))
		{
			free(abs_path);
			abs_path = ft_strjoin("/Users/", getenv("USER"));
			new_abs_path = ft_strjoin(abs_path, &args[1][1]);
		}
		else
			new_abs_path = ft_strjoin(abs_path, args[1]);
		if (chdir(new_abs_path) < 0)
			if (chdir(args[1]) < 0)
				printf("minishell: cd: no such file or directory: '%s'\n", args[1]);
		free(new_abs_path);
	}
	free_strings(args);
	free(abs_path);
}