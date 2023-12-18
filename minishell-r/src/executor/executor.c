/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:02:30 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/18 13:39:21 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Configura os descritores de arquivo para a execução do comando.
 * 
 * @param cmd            O comando atual.
 * @param next_content   O próximo comando na pipeline.
 */
void	setup_file_descriptors(t_command *cmd, t_command *next_content)
{
	if (cmd->std.in != -1)
	{
		dup2(cmd->std.in, STDIN_FILENO);
		close(cmd->std.in);
	}
	close(cmd->pipe_fd[0]);
	if (cmd->std.out != -1)
	{
		dup2(cmd->std.out, STDOUT_FILENO);
		close(cmd->std.out);
	}
	else if (next_content && next_content->cmd)
		dup2(cmd->pipe_fd[1], STDOUT_FILENO);
	close(cmd->pipe_fd[1]);
}

/**
 * Função responsável por executar um comando.
 *
 * @param cmd    O comando a ser executado.
 * @param env    O array de strings contendo as variáveis de ambiente.
 */
void	execute_command(t_command *cmd, char **env)
{
	if (cmd->redirect_error != 1)
	{
		if (cmd && cmd->built_in)
		{
			execute_built_in(cmd->cmd, cmd->redirect_error);
			free_all(true, true, true, false);
			exit(0);
		}
		else if (cmd->cmd)
			execute(cmd->cmd, env);
	}
	free_all(true, true, true, false);
	exit(shell()->exit_code);
}

/**
 * Função responsável por controlar o processo atual.
 * 
 * @param curr  Ponteiro para a lista que contém o comando atual.
 * @param env   Array de strings contendo as variáveis de ambiente.
 */
void	ctrl_process(t_list *curr, char **env)
{
	t_command	*cmd;
	t_command	*next_content;

	cmd = curr->content;
	next_content = NULL;
	if (curr->next)
		next_content = curr->next->content;
	pipe(cmd->pipe_fd);
	shell()->in_exec = true;
	cmd->proc_id = fork();
	if (cmd->proc_id == 0)
	{
		setup_file_descriptors(cmd, next_content);
		execute_command(cmd, env);
	}
	else
	{
		handle_parent_process(cmd, next_content);
	}
}

/**
 * Executa os comandos contidos na lista de segmentos.
 * 
 * @param token_list  Lista contendo os comandos a serem executados.
 */
void	execute_commands(t_list *token_list)
{
	int		status;
	t_list	*current;

	status = 0;
	current = token_list;
	while (current != NULL)
	{
		if (!current->next && ((t_command *)current->content)->redirect_error)
			shell()->exit_code = 1;
		ctrl_process(current, shell()->env);
		current = current->next;
	}
	current = token_list;
	while (current != NULL)
	{
		waitpid(((t_command *)current->content)->proc_id, &status, 0);
		current = current->next;
	}
	shell()->in_exec = false;
	if (WIFEXITED(status))
		shell()->exit_code = WEXITSTATUS(status);
}

/**
 * Função responsável por executar os comandos da lista fornecida.
 *
 * @param lst A lista de comandos a serem executados.
 */
void	executor(t_list *lst)
{
	t_command	*cmd;

	if (!lst)
		return ;
	cmd = (t_command *)lst->content;
	if (cmd->built_in && !lst->next)
		execute_single_built_in(cmd);
	else
		execute_commands(lst);
}
