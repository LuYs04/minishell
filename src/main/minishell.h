/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luatshem <luatshem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:44:01 by luatshem          #+#    #+#             */
/*   Updated: 2024/02/06 18:11:05 by luatshem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define MINISHELL  "\e\033[32mLAbash\033[0m "

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <limits.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <sys/types.h>

# include "../../libft/libft.h"
# include "../pipe/ft_pipe.h"
# include <readline/readline.h>
# include <readline/history.h>

int	g_exitcode;

typedef struct s_dol
{
	char	*buf;
	char	*str;
	int		flag;
	char	q;
}	t_dol;

typedef struct s_env
{
	char			*key;
	char			*val;
	int				flag;
	struct s_env	*next;
}	t_env;

typedef struct s_index
{
	int	cmd;
	int	op;
	int	fl;
	int	lm;
}	t_index;

typedef struct s_parse
{
	char			**cmd;
	char			**operator;
	char			**file;
	char			**delim;
	int				fd_in;
	int				fd_out;
	t_index			*index;
	struct s_parse	*next;
	struct s_parse	*prev;
}	t_parse;

typedef struct s_data
{
	char	*path;
	char	*join_path;
	char	**cmd_path;
	char	**env;
	t_env	*env_lst;
}	t_data;

void	pwd(void);
void	echo(char **args);
void	ctrl_d_exit(void);
t_parse	*error_case(int e);
void	free2d(char **arr);
void	ft_sigquit(int sig);
void	ft_sigline(int sig);
void	sig_event_loop(void);
int		valid_dir(char *path);
int		env_size(t_env *head);
void	ft_next_line(int sig);
t_env	*env_last(t_env *head);
char	*find_path(char **env);
int		lst_size(t_parse *lst);
void	data_init(t_data *data);
char	**shlvl(char **key_val);
t_parse	*pipe_split(char *line);
int		ft_exit(t_parse *input);
int		invalid_char(int symbol);
char	*join_2d_arr(char **arr);
int		ft_redirect(t_parse *lst);
int		valid_var_name(char *var);
int		builtin_compare(char *cmd);
int		check_pipe(t_parse *input);
int		dollar_word_len(char *val);
char	*check_exit_code(char *buf);
t_parse	*init_parse(t_parse *input);
int		dir_exists(const char *name);
int		ft_redirect_in(t_parse *lst);
int		ft_redirect_out(t_parse *lst);
void	cd(t_data *dt, t_parse *pars);
char	**struct_to2arr(t_parse *lst);
void	print_linked_list(t_env *head);
void	unset_valid_var_name(char *var);
char	**join_key_and_val(t_env *head);
void	check_plus(char *key, int *flag);
void	env(t_data *data, t_parse *pars);
t_parse	*parsing(char *line, t_env *env);
int		ft_redirect_heredoc(t_parse *lst);
void	unset(t_data *data, t_parse *pars);
char	*find_user(t_data *data, char *usr);
int		analyze_dollar_1(char *line, int i);
void	env_scan(char **envp, t_data *data);
int		count_buf(int i, int w, char *line);
int		count_cmd(int i, int w, char *line);
int		count_file(int i, int w, char *line);
int		count_oper(int i, int w, char *line);
void	for_export(t_data *data, char *line);
int		ft_redirect_out_append(t_parse *lst);
int		count_delim(int i, int w, char *line);
char	*ft_strjoin_nl(char *str1, char *str2);
void	ft_export(t_data *data, t_parse *pars);
void	child_ps(t_parse *input, t_data *data);
int		tilda_check(t_parse *pars, char *valid);
void	conditions(t_parse *input, t_data *data);
void	find_oldpwd(t_data **data, char *oldpwd);
char	*join_dollar(char *str, char *buf, int j);
int		check_builtin(t_parse *cmd, t_data *data);
void	env_addback(t_env **head, t_env *to_push);
void	ft_redirect_dup(t_parse *lst, int status);
void	ft_redirect_cmp(t_parse *lst, int *status);
t_env	*env_new(char *key, char *value, int flag);
int		ft_input_compare(t_parse *lst, int *status);
void	tilda(t_data *dt, t_parse *pars, char *join);
char	*file_delim_quotes(char *arg, int *i, int j);
char	*cmd_path_existence(t_data *data, char *argv);
char	**join_key_val1(char **arr, int i, t_env *lst);
void	free_input(t_parse *input_var, t_parse *input_node);
void	ft_doublelist_add_back(t_parse **lst, t_parse *new);
void	quote_handler(char *line, char *buf, int *i, int *j);
char	*fill_dollar_buf(char *buf, char *val, int i, int j);
int		args_split(char *line, t_parse *split, int i, int j);
char	*analyze_dollar(char *line, t_env *env, int i, int j);
void	init_cont_1(t_data *data, t_parse *input, char **str);
int		check_builtin_with_redirect(t_parse *cmd, t_data *data);
char	analyze_dollar_2(char *line, char q, int *flag, int *i);
void	find_variable(t_data	*data, char *line, char *pointer);
void	for_export_1(int flag, t_env *lst, char **keyvalue, int eq);
void	just_do_cd(t_data *dt, char *user, char *olddir, char *newdir);
int		check_befor_after_equol_and_plus(char **keyval, int eq, int *flag);

#endif
