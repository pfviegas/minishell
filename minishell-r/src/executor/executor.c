/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:02:30 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/04 11:40:48 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função responsável por executar um comando.
 * 
 * @param cmd   O array de strings contendo o comando e seus argumentos.
 * @param envp  O array de strings contendo as variáveis de ambiente.
 */
void execute(char **cmd, char **envp)
{
	char *path;
	char *msg;
	char *msg_aux;

//	path recebe o caminho do comando
	path = find_path(envp, cmd[0]);
	msg = NULL;
	msg_aux = NULL;

//	verifica se o caminho do comando é um diretório
	check_dir(path);
//	executa o comando	
	if (execve(path, cmd, envp) == -1)
	{
		//EFAULT (14) - Bad address
		if (errno == 14)
		{
			display_error(127, "minishell: Bad address", true);
		}
		//ENOENT (2) - No such file or directory
		else if (errno == 2)
		{
			if ((!ft_strncmp("./", path, 2) || path[0] == '/'))
			{
				msg_aux = ft_strjoin("minishell: ", path);
				msg = ft_strjoin(msg_aux, ": No such file or directory");
				display_error(127, msg, true);
			}
			else
			{
				msg = ft_strjoin(path, ": command not found");
				display_error(127, msg, true);
			}
		}
		else if (errno == 13)
		{
			msg_aux = ft_strjoin("minishell: ", path);
			msg = ft_strjoin(msg_aux, ": Permission denied");
			display_error(126, msg, true);	
		}
		else
		{
			msg_aux = ft_strjoin("minishell: ", path);
			msg = ft_strjoin(msg_aux, ": command not found");
			display_error(127, msg, true);
		}
	}
	free(msg);
	free(msg_aux);
	free(path);
}

/**
 * Função responsável por controlar o processo atual e executar os comandos.
 * 
 * @param curr  Ponteiro para a lista que contém o comando atual.
 * @param env   Array de strings contendo as variáveis de ambiente.
 */
void	ctrl_process(t_list *curr, char **env)
{
	t_command	*cmd;
	t_command	*next_content;

// 	cmd recebe o comando atual
	cmd = curr->content;
//	inicializa o next_content para receber o proximo comando
	next_content = NULL;
//	verifica se o proximo comando existe	
	if (curr->next)
		next_content = curr->next->content;
//	cria um pipe para o comando atual
	pipe(cmd->pipe_fd);
//	atualiza o status de execucao do shell
	shell()->in_exec = true;
//	cria um processo filho
	cmd->proc_id = fork();
//	verifica se o processo é o filho
	if (cmd->proc_id == 0)
	{
// 		Se o comando atual for o primeiro da lista, redireciona a entrada padrão
		if (cmd->std.in != -1)
		{
			dup2(cmd->std.in, STDIN_FILENO);
			close(cmd->std.in);
		}
		close(cmd->pipe_fd[0]);
// 		Se o comando atual for o último da lista, redireciona a saída padrão
		if (cmd->std.out != -1)
		{
			dup2(cmd->std.out, STDOUT_FILENO);
			close(cmd->std.out);
		}
// 		Se o comando atual não for o último da lista, redireciona a saída padrão para o pipe
		else if (next_content && next_content->cmd)
			dup2(cmd->pipe_fd[1], STDOUT_FILENO);
		close(cmd->pipe_fd[1]);
// 		verifica se ocorreu um erro de redirecionamento
		if (cmd->redirect_error != 1)
		{
// 			verifica se o comando atual é um comando built-in
			if (cmd && cmd->built_in)
			{
// 				executa o comando built-in
				execute_built_in(cmd->cmd, cmd->redirect_error);
// 				libera a memoria alocada
				free_all(true, true, true, false);
// 				termina o processo filho com exit_code 0
				exit(0);
			}
// 			verifica se o comando atual é um comando externo
			else if (cmd->cmd)
				execute(cmd->cmd, env);
		}
//		libera a memoria alocada
		free_all(true, true, true, false);
//		termina o processo filho com exit_code 0
		exit(shell()->exit_code);
	}
//	verifica se o processo é o pai
	else
	{
//		Verifica se next_content não é nulo e 
//		se possui um comando (next_content->cmd) e 
//		se o descritor de arquivo de entrada (next_content->std.in) é igual a -1.
		if (next_content && next_content->cmd && next_content->std.in == -1)
			next_content->std.in = dup(cmd->pipe_fd[0]);
//		fecha os descritores de arquivo se necessário
		if (cmd->std.in != -1)
			close(cmd->std.in);
		if (cmd->std.out != -1)
			close(cmd->std.out);
		close(cmd->pipe_fd[0]);
		close(cmd->pipe_fd[1]);
	}
}

/**
 * Executa os comandos contidos na lista de segmentos.
 * 
 * @param token_list  Lista contendo os comandos a serem executados.
 */
void execute_commands(t_list *token_list)
{
	int status;
	t_list *current;

	status = 0;
	current = token_list;
	// Executa cada segmento de comando
	while (current != NULL)
	{
		if (!current->next && ((t_command *)current->content)->redirect_error)
			shell()->exit_code = 1;
		ctrl_process(current, shell()->env);
		current = current->next;
	}
	current = token_list;
	// Aguarda a finalização de cada processo filho
	while (current != NULL)
	{
		waitpid(((t_command *)current->content)->proc_id, &status, 0);
		current = current->next;
	}
//	atualiza o status de execucao do shell
	shell()->in_exec = false;
	// Define o código de saída com base no status de finalização
	if (WIFEXITED(status))
		shell()->exit_code = WEXITSTATUS(status);
}

/**
 * Função responsável por executar os comandos da lista fornecida.
 *
 * @param lst A lista de comandos a serem executados.
 */
void executor(t_list *lst)
{
	t_command *cmd;

//	verifica se a lista é nula
	if (!lst)
		return;
//	cmd recebe o primeiro comando da lista
	cmd = (t_command *)lst->content;
//	verifica se a lista contém apenas um comando built-in ou varios comandos
	if (cmd->built_in && !lst->next)
//		executa o comando unico built-in	
		execute_single_built_in(cmd);
	else
//		executa os comandos da lista	
		execute_commands(lst);
}
