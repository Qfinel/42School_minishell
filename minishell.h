/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdukic <sdukic@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/21 17:37:50 by sdukic           ###   ########.fr       */
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
int		is_redirect(char *input);
void	handle_redirect(t_vars *vars, char *input);
int		is_builtin(t_vars *vars, char *input, char **args);
int		contains_spaces(char *str);

//parser

char	*get_cmd(char **paths, char *cmd);

//executor

void	execute_cmd(t_vars *vars, char *input);
int		count_pipes(t_vars *vars);
int		count_pipes_outside_quotes(t_vars *vars);
void	handle_pipes(t_vars *vars);

int		count_words_starting_with_dollar(char *str);

//Replaces variables starting with $ with their value in the input string.
t_vars	replace_envvar_with_value(t_vars vars);

char	**split_with_quotes(char *str);

char	*remove_unclosed_quotes(char *str);

#endif
