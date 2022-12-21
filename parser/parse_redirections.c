/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 11:36:38 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/21 17:43:45 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_to_file(t_vars *vars, char *args, char *filename, char **strs)
{
	int	outfd;
	int	id;

	filename = ft_strtrim(filename, " ");
	if (contains_spaces(filename))
		printf("minishell: err: invalid filename\n");
	else
	{
		id = fork();
		if (id == 0)
		{
			outfd = open(filename, O_WRONLY | O_APPEND | O_CREAT);
			dup2(outfd, 1);
			execute_cmd(vars, args);
			close(outfd);
			free_strings(strs);
			free_strings(vars->envp);
			free_strings(vars->paths);
			free(filename);
			exit(0);
		}
		else
			wait(NULL);
	}
	free(filename);
}

void	output_to_file(t_vars *vars, char *args, char *filename, char **strs)
{
	int	outfd;
	int	id;

	filename = ft_strtrim(filename, " ");
	if (contains_spaces(filename))
		printf("minishell: err: invalid filename\n");
	else
	{
		id = fork();
		if (id == 0)
		{
			outfd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(outfd, 1);
			execute_cmd(vars, args);
			close(outfd);
			free_strings(strs);
			free_strings(vars->envp);
			free_strings(vars->paths);
			free(filename);
			exit(0);
		}
		else
			wait(NULL);
	}
	free(filename);
}

// void	read_until_from_file(t_vars *vars, char *args, char *filename, char **strs)
// {
// 	return;
// }

void	read_from_file(t_vars *vars, char *args, char *filename, char **strs)
{
	int	infd;
	int	id;

	filename = ft_strtrim(filename, " ");
	id = fork();
	if (id == 0)
	{
		infd = open(filename, O_RDONLY);
		if (infd < 0)
			printf("minishell: err: couldn't open the file");
		else
		{
			dup2(infd, 0);
			execute_cmd(vars, args);
			close(infd);
		}
		free_strings(strs);
		free_strings(vars->envp);
		free_strings(vars->paths);
		free(filename);
		exit(0);
	}
		else
			wait(NULL);
	free(filename);
}

int	is_redirect(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			return (1);
		i++;
	}
	return (0);
}

void	handle_redirect(t_vars *vars, char *input)
{
	char	**strs;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strdup(input);
	while (tmp[i])
	{
		if (tmp[i] == '<')
			tmp[i] = '>';
		i++;
	}
	strs = ft_split(tmp, '>');
	free(tmp);
	i = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
		{
			if (input[i] == '>' && input[i + 1] == '>')
			{
				append_to_file(vars, strs[j], strs[j + 1], strs);
				i++;
			}
			else if (input[i] == '>' && input[i + 1] != '>')
				output_to_file(vars, strs[j], strs[j + 1], strs);
			// else if (input[i] == '<' && input[i + 1] == '<')
			// {
			// 	read_until_from_file(vars, strs[j], strs[j + 1], strs);
			// 	i++;
			// }
			else if (input[i] == '<' && input[i + 1] != '<')
				read_from_file(vars, strs[j], strs[j + 1], strs);
			j++;
		}
		i++;
	}
	free_strings(strs);
}
