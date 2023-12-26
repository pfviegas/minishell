/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:11:39 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/26 18:21:39 by pveiga-c         ###   ########.fr       */
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
char	*build_error_message(char *path, int cmd_not_found)
{
	char	*msg;
	char	*msg_aux;

	msg = NULL;
	msg_aux = ft_strjoin("minishell: ", path);
	if (errno == 2)
	{
		if (cmd_not_found == 0)
			msg = ft_strjoin(msg_aux, ": No such file or directory");
		else
		{
			if (ft_strchr(path, '/') == NULL)
				msg = ft_strjoin(path, ": command not found");
			else
				msg = ft_strjoin(msg_aux, ": No such file or directory");
		}
	}
	else if (errno == 8)
		msg = ft_strjoin(path, ": Invalid executable format");
	else if (errno == 13)
	{
		if (access(path, X_OK))
			msg = ft_strjoin(msg_aux, ": Permission denied");
	}
	else if (errno == 14)
		msg = ft_strjoin(msg_aux, ": No such file or directory");
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

	msg = build_error_message(path, 1);
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
errno = 0;        // 0 Nenhum erro
errno = EPERM;    // 1 Operação não permitida
errno = ENOENT;   // 2 Arquivo ou diretório não encontrado
errno = ESRCH;    // 3 Processo não encontrado
errno = EINTR;    // 4 Chamada de sistema interrompida por sinal
errno = EIO;      // 5 Erro de entrada/saída
errno = ENXIO;    // 6 Dispositivo ou endereço inválido
errno = E2BIG;    // 7 Argumento muito grande
errno = ENOEXEC;  // 8 Execução de formato inválido
errno = EBADF;    // 9 Descritor de arquivo ruim
errno = ECHILD;   // 10 Sem processos filhos
errno = EAGAIN;   // 11 Recurso temporariamente indisponível
errno = ENOMEM;   // 12 Falta de espaço de memória
errno = EACCES;   // 13 Permissão negada
errno = EFAULT;   // 14 Endereço de memória inválido
errno = ENOTBLK;  // 15 Bloco de dispositivo esperado
errno = EBUSY;    // 16 Dispositivo ou recurso está ocupado
errno = EEXIST;   // 17 Arquivo ou diretório já existe
errno = EXDEV;    // 18 Operação de link cruzado não permitida
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
