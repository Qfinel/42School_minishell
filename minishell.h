/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/17 21:17:39 by sdukic           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef struct s_vars
{
	char	*input;
	char	**paths;
	char	**envp;
}	t_vars;

void	ft_cd(char **args);
void	ft_pwd(char **args);
void	ft_echo(char *line, char **args);
void	ft_env(t_vars *vars, char **args);
void	ft_export(t_vars *vars, char **args);
void	ft_unset(t_vars *vars, char **args);
void	ctrl_c_handler();
int		ft_arr_len(char **arr);
void	close_minishell(t_vars *vars, int exit_sign);
void	free_strings(char **strings);
char	*get_cmd(char **paths, char *cmd);
int		is_redirect(char *input);
void	handle_redirect(t_vars *vars, char *input);
int		is_builtin(t_vars *vars, char *input, char **args);
int		contains_spaces(char *str);
void	execute_cmd(t_vars *vars, char *input);

//Replaces variables starting with $ with their value in the input string.
void	replace_envvar_with_value(t_vars *vars);

#endif
