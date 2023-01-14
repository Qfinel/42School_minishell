/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/14 17:39:00 by jtsizik          ###   ########.fr       */
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
# include <sys/stat.h>
# include "libft/libft.h"

int	g_exit;

typedef struct s_vars
{
	char	**paths;
	char	**envp;
	char	*input;
}	t_vars;

typedef struct s_redir
{
	char			*filename;
	char			*type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_pipes
{
	int				outfd;
	int				infd;
	char			*cmd;
	struct s_pipes	*next;
}	t_pipes;

typedef struct s_cmd
{
	char	*command;
	char	**args;
	t_redir	*redirs;

}	t_cmd;

typedef struct s_vector
{
	int	i;
	int	j;
}	t_vector;

typedef struct s_3dvector
{
	int	i;
	int	j;
	int	k;
}	t_3dvector;

void	ft_cd(t_vars *vars, t_cmd *cmd);
void	ft_pwd(void);
void	ft_echo(t_cmd *cmd);
void	ft_env(t_vars *vars, char **args);
void	ft_export(t_vars *vars, char **args);
void	ft_unset(t_vars *vars, char **args);
void	ctrl_c_handler(int sig);
void	ctrl_c_pipe_handler(int sig);
int		ft_arr_len(char **arr);
void	close_minishell(t_vars *vars, char *input);
void	free_strings(char **strings);
char	*get_cmd(char **paths, char *cmd);
int		is_builtin(t_vars *vars, t_cmd *cmd);
int		contains_spaces(char *str);
void	exec_cmd(t_vars *vars, char *input);
void	free_cmd(t_cmd *cmd);
t_cmd	*parse_cmd(t_vars *vars, char *input);
t_redir	*parse_redirections(char *input);
int		redirections_exist(char *input);
void	exit_process(t_vars *vars);
char	**split_with_quotes(char *str);
char	*replace_envvar_with_value(t_vars vars, char *input);
char	**split_true_pipes(char *input);
char	*get_env_value(t_vars *vars, char *key);
int		is_real(char *input, int i);
char	**ft_split_pipes(char *s);
int		contains_index(int *indexes, int i);
int		is_important_var(char **args);
int		count_env_vars(t_vars *vars, char **args);
void	get_command(t_cmd *cmd, t_vars *vars);
int		paths_exist(char **envp);
char	*ft_str_replace(char *str, char *old, char *new);
int		count_words_starting_with_dollar(char *str);
char	*get_end_of_envvar(char *str);
int		unclosed_quotes(char *input);
void	check_exit(char *input);
char	*replace_shlvl(char *str);
void	process_int(int sig);
void	exec_heredoc(t_vars *vars, t_cmd *cmd, t_pipes *pipes);
void	truncate_tmp(void);
void	add_to_tmp(char *input);
void	delete_tmp(t_vars *vars);
void	get_paths(t_vars *vars);
void	free_pipes(t_pipes *pipes);
void	pipe_loop(t_vars *vars, char *input);
t_pipes	*parse_pipes(char **cmds);
void	change_oldpwd(t_vars *vars);
void	change_pwd(t_vars *vars);
int		only_slashes(char *str);
int		is_quote(char c);
char	get_opening_quote(char quote, char c);
int		ft_intarrlen(int *arr);
int		already_exist(char **envp, char *arg);
void	print_export_vars(t_vars *vars, char **new_envp);

#endif
