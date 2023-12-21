/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:11:39 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/21 16:20:04 by pviegas          ###   ########.fr       */
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
	if (path)
	{
		if (execve(path, cmd, envp) == -1)
		{
			handle_execution_error(path);
		}
		free(path);
	}
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
		if (ft_strchr(path, '/'))
			msg = ft_strjoin(msg_aux, ": No such file or directory");
		else
			msg = ft_strjoin(path, ": command not found");
	}
	else if (errno == 8)
		msg = ft_strjoin(path, ": Invalid executable format");
	else if (errno == 13)
	{
		if (access(path, X_OK))
			msg = ft_strjoin(msg_aux, ": Permission denied");
	}
	else if (errno == 14)
		msg = ft_strjoin(msg_aux, ": command not found");
	else
		msg = ft_strjoin(path, ": command not found");
	free(msg_aux);
	return (msg);
}

/**
 * Função responsável por lidar com erros de execução.
 * 
 * @param path  O caminho que causou o erro.
 */
void	handle_execution_error(char *path)
{
	char	*msg;

	msg = build_error_message(path);
	if (errno == 8)
		display_error(0, msg, true);
	else if (errno == 13)
		display_error(126, msg, true);
	else
		display_error(127, msg, true);
	free(msg);
}
/*
// Exemplos de códigos de erro e suas definições
errno = 0;        // Nenhum erro
errno = EPERM;    // Operação não permitida
errno = ENOENT;   // Arquivo ou diretório não encontrado
errno = ESRCH;    // Processo não encontrado
errno = EINTR;    // Chamada de sistema interrompida por sinal
errno = EIO;      // Erro de entrada/saída
errno = ENXIO;    // Dispositivo ou endereço inválido
errno = E2BIG;    // Argumento muito grande
errno = ENOEXEC;  // Execução de formato inválido
errno = EBADF;    // Descritor de arquivo ruim
errno = ECHILD;   // Sem processos filhos
errno = EAGAIN;   // Recurso temporariamente indisponível
errno = ENOMEM;   // Falta de espaço de memória
errno = EACCES;   // Permissão negada
errno = EFAULT;   // Endereço de memória inválido
errno = ENOTBLK;  // Bloco de dispositivo esperado
errno = EBUSY;    // Dispositivo ou recurso está ocupado
errno = EEXIST;   // Arquivo ou diretório já existe
errno = EXDEV;    // Operação de link cruzado não permitida
errno = ENODEV;   // Sem tal dispositivo
errno = ENOTDIR;  // Não é um diretório
errno = EISDIR;   // É um diretório
errno = EINVAL;   // Argumento inválido
errno = ENFILE;   // Muitos arquivos abertos no sistema
errno = EMFILE;   // Muitos arquivos abertos por processo
errno = ENOTTY;   // Não é um terminal
errno = ETXTBSY;  // Texto do arquivo ocupado
errno = EFBIG;    // Arquivo muito grande
errno = ENOSPC;   // Sem espaço no dispositivo
errno = ESPIPE;   // Operação ilegal de busca
errno = EROFS;    // Sistema de arquivos somente leitura
errno = EMLINK;   // Muitas ligações
errno = EPIPE;    // Conexão quebrada
errno = EDOM;     // Argumento de domínio de função matemática inválido
errno = ERANGE;   // Resultado fora do intervalo
*/
