/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:54:41 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/07 16:27:09 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função responsável por lidar com o processo pai.
 * 
 * Esta função fecha os descritores de arquivo do comando atual 
 * e do próximo comando, além de redirecionar a entrada padrão 
 * do próximo comando para o descritor de arquivo de leitura do 
 * pipe do comando atual, se necessário.
 * 
 * @param cmd            O comando atual.
 * @param next_content   O próximo comando.
 */
void	handle_parent_process(t_command *cmd, t_command *next_content)
{
	if (next_content && next_content->cmd && next_content->std.in == -1)
		next_content->std.in = dup(cmd->pipe_fd[0]);
	if (cmd->std.in != -1)
		close(cmd->std.in);
	if (cmd->std.out != -1)
		close(cmd->std.out);
	close(cmd->pipe_fd[0]);
	close(cmd->pipe_fd[1]);
}

/**
 * Função responsável por executar um comando.
 * 
 * @param cmd   O comando a ser executado.
 * @param envp  O array de strings contendo as variáveis de ambiente.
 */
void	execute(char **cmd, char **envp)
{
	char	*path;

	path = find_path(envp, cmd[0]);
	check_dir(path);
	if (execve(path, cmd, envp) == -1)
	{
		handle_execution_error(path);
	}
	free(path);
}

/**
 * Constrói a mensagem de erro com base no caminho fornecido.
 *
 * @param path  O caminho que causou o erro.
 * @return      A mensagem de erro construída.
 */
static char	*build_error_message(char *path)
{
	char	*msg;
	char	*msg_aux;

	msg = NULL;
	msg_aux = ft_strjoin("minishell: ", path);
	if (errno == 2)
	{
		if ((!ft_strncmp("./", path, 2) || path[0] == '/'))
			msg = ft_strjoin(msg_aux, ": No such file or directory");
		else
			msg = ft_strjoin(path, ": command not found");
	}
	else if (errno == 13)
		msg = ft_strjoin(msg_aux, ": Permission denied");
	else
		msg = ft_strjoin(msg_aux, ": command not found");
	free(msg_aux);
	return (msg);
}

// Função para lidar com erros durante a execução
void	handle_execution_error(char *path)
{
	char	*msg_aux;
	char	*msg;

	msg = build_error_message(path);
	msg_aux = ft_strjoin("minishell: ", path);
	if (errno == 14)
	{
		display_error(127, "minishell: Bad address", true);
	}
	else
	{
		display_error(127, msg, true);
	}
	free(msg_aux);
	free(msg);
}
