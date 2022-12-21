/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:07:28 by sdukic            #+#    #+#             */
/*   Updated: 2022/12/21 17:12:06 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_cmd(t_vars *vars, char *input)
{
	char	*cmd;
	char	**args;
	int		id;
	// char	**pasrsed_input;


	if (is_redirect(input))
		return (handle_redirect(vars, input));
	input = remove_unclosed_quotes(input);
	args = split_with_quotes(input);
	// args = ft_split(input, ' ');
	if (!args[0])
		return(free(args));
	if (is_builtin(vars, input, args))
		return ;
	if (args[0][0] == '/')
	{
		if (access(args[0], F_OK) == 0)
			cmd = ft_strdup(args[0]);
		else
			cmd = NULL;
	}
	else
		cmd = get_cmd(vars->paths, args[0]);
	if (cmd)
	{
		id = fork();
		if (id == 0)
			execve(cmd, args, vars->envp);
		wait(NULL);
	}
	else
		printf("minishell: command not found: '%s'\n", args[0]);
	free_strings(args);
	free(cmd);
}
