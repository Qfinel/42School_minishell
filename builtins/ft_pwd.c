/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 16:05:29 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/15 16:08:54 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(char **args)
{
	if (args[1])
		printf("minishell: pwd: too many arguments\n");
	else
		printf("%s\n", getcwd(NULL, 0));
	free_strings(args);
}