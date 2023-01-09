/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtsizik <jtsizik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 16:24:14 by jtsizik           #+#    #+#             */
/*   Updated: 2023/01/09 18:43:56 by jtsizik          ###   ########.fr       */
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

void	ft_cd(t_vars *vars, t_cmd *cmd);
void	ft_pwd(char **args);
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
void	exec_pipes(t_vars *vars, char *input);
void	exec_cmd(t_vars *vars, char *input, char **cmds);
void	free_cmd(t_cmd *cmd);
t_cmd	*parse_cmd(t_vars *vars, char *input);
t_redir	*parse_redirections(char *input);
int		redirections_exist(char *input);
void	exit_process(t_vars *vars);
char	**split_with_quotes(char *str);
char	*replace_envvar_with_value(t_vars vars, char *input);
char	**split_true_pipes(char *input);
char	*get_env_value(t_vars *vars, char *key);
int		is_real_pipe(char *input, int i);
int		is_real_redir(char *input, int i);
char	**ft_split_pipes(char *s);
int		contains_index(int *indexes, int i);
int		is_important_var(char **args);
int		count_env_vars(t_vars *vars, char **args);
void	get_command(t_cmd *cmd, t_vars *vars);
int		paths_exist(char **envp);
char	*ft_str_replace(char *str, char *old, char *new);
int		count_words_starting_with_dollar(char *str);
char	*get_end_of_envvar(char *str);
int		skip_to_next(char c, char *str);
int		unclosed_quotes(char *input);
void	check_exit(char *input);
char	*replace_shlvl(char *str);
void	process_int(int sig);
void	exec_heredoc(t_vars *vars, t_cmd *cmd, char **cmds);
void	truncate_tmp(void);

#endif
