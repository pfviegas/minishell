/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:35:04 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 17:20:59 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * Executa os comandos fornecidos.
 * 
 * @param command Os comandos a serem executados.
 */
void executor(t_commands *command)
{
	pid_t proc_id;
	int status;

	execution(command);

	lst_first(&command);
	while (command)
	{
		if (command->content[0])
		{
			proc_id = waitpid(-1, &status, 0);
			if (proc_id != -1 && WIFEXITED(status))
				g_var.exit_status = WEXITSTATUS(status);
		}
		if (!command->next)
			break;
		command = command->next;
	}
	if (check_fds(command))
		g_var.exit_status = 1;
}

/**
 * Executa uma série de comandos.
 * 
 * @param command Um ponteiro para o primeiro comando da série.
 */
void execution(t_commands *command)
{
	char **env_vars;

	command->path = NULL;
	while (command)
	{
		if (command->content[0] && !command->fd_master_error[0] && !command->fd_master_error[1])
		{
			env_vars = lst_to_arr(g_var.env);
			command->path = get_cmd_path(env_vars, command->content);
			free_str_array(&env_vars);
			choose_execution(command);
			command_execution(command);
		}
		if (!command->next)
			break;
		command = command->next;
	}
}

// Define a funcao a executar para cada node 
// E executada atraves da instrucao "command->ft_exec(&command);"
void	choose_execution(t_commands *command)
{
	if (!ft_strncmp(command->content[0], "pwd", 3))
		command->ft_exec = execute_pwd;
	else if (!ft_strncmp(command->content[0], "cd", 2))
		command->ft_exec = execute_cd;
//		printf("executar CD\n\n");
	else if (!ft_strncmp(command->content[0], "echo", 4))
		command->ft_exec = execute_echo;
	else if (!ft_strncmp(command->content[0], "env", 3))
		command->ft_exec = execute_env;
	else if (!ft_strncmp(command->content[0], "exit", 4))
		command->ft_exec = execute_exit;
	else if (!ft_strncmp(command->content[0], "export", 6))		
		command->ft_exec = execute_export;
//		printf("executar EXPORT\n\n");
	else if (!ft_strncmp(command->content[0], "unset", 5))
		command->ft_exec = execute_unset;
//		printf("executar UNSET\n\n");
	else
		command->ft_exec = execute_default;
//		printf("executar DEFAULT\n\n");
}

void	command_execution(t_commands *command)
{
	// se o comando for built-in e nao tiver pipes
	if (is_built_in(command) && (lst_size(command) == 1))
	{
		// executa o comando built-in
		command->ft_exec(&command);
		// se o comando for exit, libera a memoria e encerra
		if (command->content && (!ft_strncmp(command->content[0], "exit", 5)) && \
		free_env(&g_var.env) && free_vars() && write(2, "exit\n", 5))
			exit(g_var.exit_status);
		return ;
	}
	if (fork() == 0)
	{
		if (command->prev && command->fd_master[0] < 3)
			dup2(command->fd[0], 0);
		else if (command->fd_master[0] > 2)
			dup2(command->fd_master[0], 0);
		if (command->next && command->fd_master[1] < 3)
			dup2(command->next->fd[1], 1);
		else if (command->fd_master[1] > 2)
			dup2(command->fd_master[1], 1);
		command->ft_exec(&command);
		free_env(&g_var.env);
		free_vars();
		close(0);
		exit(g_var.exit_status);
	}
	close_fds(&command, 0);
}
