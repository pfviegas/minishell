/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:49:21 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 14:15:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ------------------------------- INCLUDES --------------------------------- //

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

#include "../libft/libft.h"
#include "built_in.h"
//#include "aux.h"

// -------------------------------- MACROS ---------------------------------- //

// ------------------------------- STRUCTS ---------------------------------- //

typedef struct s_commands
{
	char				**content;
	char				*path;
	int					fd_master[2];
	int					fd[2];
	int					fd_master_error[2];		// guarda se o fd_master for invalido
	struct s_commands	*next;
	struct s_commands	*prev;
	void				(*ft_exec)(struct s_commands **commands);
}	t_commands;

typedef struct s_vars
{
	t_commands		*head;
	char			*str;
	char			**env;
	char			**division;
}	t_vars;

typedef struct s_env
{
	char			*data;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

struct s_global
{
	t_vars			*vars;
	int				exit_status;
	t_env			*env;
	int				here_doc;
	int				interrupted;
//	struct termios	termios_save;
};

extern struct s_global	g_var;

// -----------------------------  FUNCTIONS --------------------------------- //

t_vars		*init_vars(void);
void		signals_behavior(void);
void		prompt(void);
void		syntax_handling(char *input);
int 		check_redir_pipe(char *str, int *arr);
void		syntax_handling(char *input);
void		syntax_error(char *str, char *input, int size);
void		quotes_handling(char *input, int i, int *flag);
t_commands	*generate_tokens(char *input);
void		parsing(char *res, char *str, char sep, int *arr);
char		**expander(char **division, char **env);
void 		expander_aux(char ***division, char **env, int *i, int *k);
void		expander_aux_loop(char ***division, char **env, int *i, int *k);
char		*chg_dollar(char *input, char **env);
void 		chg_dollar_loop(char **input, char **buf, int *i, int *j);
char		*replace_str(char *str, char *s1, char *s2);
char		**split_by_quotes(char *str);
char 		*prepare_str(char *str, int i, int size);
t_commands	*lst_new(int i);
void		tokens_redirection(t_commands *lst, char **division);
void 		delete_quotes(char **input);
int 		here_doc(char *str);
void		here_doc_signals(int sign);
void		signals_behavior(void);

t_env		*get_env_var(char **env);
t_env		*env_last(t_env *lst);
void		env_add_back(t_env **lst, t_env *new);
t_env		*env_new(char *str);
int			free_env(t_env **lst);
void		env_first(t_env **lst);
void		executor(t_commands *command);
void		execution(t_commands *command);
void		print_lst(t_commands *command);
char		**lst_to_arr(t_env *lst_env);
int			env_lst_size(t_env *lst);
t_commands	*lst_last(t_commands *lst);
void		lst_add_back(t_commands **lst, t_commands *new);
char		*get_cmd_path(char **env, char **cmd);
char		*env_search_str(char **env, char *str);
int			search_number(char *s1, char *s2);
void		free_str_array(char ***str_array);
void		choose_execution(t_commands *command);
void		command_execution(t_commands *command);
int			is_built_in(t_commands *command);
int			lst_size(t_commands *lst);
int			free_vars(void);
void		free_list(t_commands **lst);
void		lst_first(t_commands **lst);
void		execute_env(t_commands **command);
void		execute_pwd(t_commands **command);
int			ft_isspace(int c);
void		execute_echo(t_commands **command);
void		execute_exit(t_commands **command);
void		stderr_null(void);
void		execute_export(t_commands **command);
void		sort_array(char **arr, int size);
int			str_cmp(char *s1, char *s2);
int			strlen_array(char **array);
void		execute_unset(t_commands **command);
t_env		*env_search(char *input_var);
void		execute_cd(t_commands **lst);
int			ft_strcmp(char *s1, char *s2);
int			str_is_alphanum(char *str);
void		execute_default(t_commands **command);
void		close_fds(t_commands **command, int flag);
void		error_handle(char *cmd);
void		is_a_directory(char *cmd);
void		command_not_found(char *cmd);
int			check_fds(t_commands *command);

#endif