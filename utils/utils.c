/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:38:31 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/15 13:37:28 by jtsizik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	contains_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	exit_process(t_vars *vars)
{
	if (vars->paths)
		free_strings(vars->paths);
	if (vars->envp)
		free_strings(vars->envp);
	if (vars->input)
		free(vars->input);
	exit(g_exit);
}

int	check_if_real_quote(char *input, int type, int num)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	num -= 1;
	while (input[i])
	{
		if (input[i] == '\'' && type == 1 && counter == num)
			break ;
		else if (input[i] == '\'' && type == 1)
			counter++;
		if (input[i] == '\"' && type == 2 && counter == num)
			break ;
		else if (input[i] == '\"' && type == 2)
			counter++;
		i++;
	}
	if (is_real(input, i) || !input[i + 1] || i == 0)
		return (1);
	else
		return (0);
}

int	unclosed_quotes(char *input)
{
	char	**args;

	args = split_with_quotes(input);
	if (!args)
		return (printf("error: unclosed quotes\n"));
	free_strings(args);
	return (0);
}
