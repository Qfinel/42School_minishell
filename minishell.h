/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 17:26:22 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/16 15:24:37 by jtsizik          ###   ########.fr       */
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
	int		pipes;
	int		redirections;
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
int		is_builtin(t_vars *vars, char **args);

#endif