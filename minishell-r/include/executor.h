/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:54:25 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 14:52:09 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

int		here_doc(t_command *cmd);
void	executor(t_list *lst);
void	execute_built_in(char **cmd, int seg_error);
void	execute_single_built_in(t_command *seg);
void 	execute_built_in(char **cmd, int seg_error);
char	*find_path(char **envp, char *cmd);
void	execute_cd(char **command);
void	execute_echo(char **cmd);
void	execute_env(char **cmd);
void	execute_pwd(void);
void	execute_unset(char	**cmd);
void	execute_export(char	**cmd);

void	rm_str_from_array(char ***array, int index);

#endif