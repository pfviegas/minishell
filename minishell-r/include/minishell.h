/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:10:41 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/29 14:11:30 by pveiga-c         ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <term.h> 
# include <termios.h>
# include "parsing.h"
# include "utils.h"
# include "executor.h"

typedef struct s_shell
{
	bool			prompt;
	bool			error;
	t_list			*segments_lst;
	char			**env;
	int				exit_code;
	bool			in_here_doc;
	int				here_doc_fd[2];
	bool			in_exec;
	char			*rep_prompt;
}	t_shell;

t_shell	*shell(void);

void	signals_behavior(void);
void	init_shell_vars(t_shell *sh, char **envp);
char	**get_env_vars(char **envp);
char	**cp_array(char **array);
char	*get_env_var_name(char *str);
void	update_env(char	***env, char *cmd);
void	add_char(char **str, char c);
void	add_str_to_array(char ***array, char *str);
char	**create_array(char *str);
void	print_matriz(char **matriz);

#endif
