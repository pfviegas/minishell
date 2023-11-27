/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:56:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/27 14:07:49 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"

# include <stdio.h>
# include <signal.h>
# include <limits.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
#include <sys/wait.h>

# include "parsing.h"
# include "utils.h"
# include "executor.h"

typedef struct s_shell
{
	bool	prompt;
	bool	error;
	t_list	*segment_lst;
	char	**env;
	int		exit_code;
	bool	in_here_doc;
	int		here_doc_fd[2];
	bool	in_exec;
}	t_shell;

t_shell	*shell(void);

void	signals_behavior(void);
void	init_shell_vars(t_shell *sh, char **envp);
char	**get_env_vars(char **envp);
char	**cp_array(char **array);
char	*get_env_var_name(char *str);
//void	update_shlvl(char ***env, char *value);
void	update_env(char	***env, char *cmd);

void	add_char(char **str, char c);
void	add_str_to_array(char ***array, char *str);
//int		find_env_var(char **env, char *var);
char	**create_array(char *str);


#endif
