/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:54:25 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/20 17:07:26 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		here_doc(t_command *cmd);
void	executor(t_list *lst);
void	execute_built_in(char **cmd, int seg_error);
void	execute_single_built_in(t_command *seg);
void	execute_built_in(char **cmd, int seg_error);
char	*find_path(char **envp, char *cmd);
void	execute_cd(char **command);
void	execute_echo(char **cmd);
void	execute_env(char **cmd);
void	execute_pwd(void);
void	get_pwd(char ***env);
void	execute_unset(char	**cmd);
void	execute_export(char	**cmd);
void	execute_exit(char **cmd);
void	rm_str_from_array(char ***array, int index);
void	check_dir(char *path);
void	close_here_doc(void);
void	here_doc_expand_var(char **line, t_command *cmd);
void	here_doc_error(char *str);
void	sig_here_doc(int signal);
void	redirect_standard_input(t_command *token, int *saved_stdin);
void	redirect_standard_output(t_command *token, int *saved_stdout);
void	restore_standard_input(int saved_stdin);
void	restore_standard_output(int saved_stdout);
void	handle_execution_error(char *path);
void	execute(char **cmd, char **envp);
void	handle_parent_process(t_command *cmd, t_command *next_content);
void	execute_cd_error(char *path);
int		find_env_var(char **env, char *var);

#endif