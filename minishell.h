/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2022/12/22 15:52:16 by jtsizik          ###   ########.fr       */
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
	char	**paths;
	char	**envp;
}	t_vars;

typedef struct s_redir
{
	char			*filename;
	char			*type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char	*command;
	char	**args;
	t_redir	*redirs;

}	t_cmd;

void	ft_cd(t_vars *vars, t_cmd *cmd);
void	ft_pwd(char **args);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_vars *vars, char **args);
void	ft_export(t_vars *vars, char **args);
void	ft_unset(t_vars *vars, char **args);
void	ctrl_c_handler(int sig);
void	ctrl_c_pipe_handler(int sig);
int		ft_arr_len(char **arr);
void	close_minishell(t_vars *vars, int exit_sign, char *input);
void	free_strings(char **strings);
char	*get_cmd(char **paths, char *cmd);
int		is_builtin(t_vars *vars, t_cmd *cmd);
int		contains_spaces(char *str);
void	exec_pipes(t_vars *vars, char *input);
void	exec_cmd(t_vars *vars, char *input);
void	free_cmd(t_cmd *cmd);
t_cmd	*parse_cmd(t_vars *vars, char *input);
t_redir	*parse_redirections(char *input);
char	**ft_split_charset(char *str, char *charset);
void	exit_process(t_vars *vars);
void	do_redirections(t_vars *vars, t_cmd *cmd);

#endif