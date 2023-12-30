/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:12:04 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/30 10:43:41 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Verifica se a linha fornecida é válida para o comando atual.
 * 
 * @param line A linha a ser verificada.
 * @param cmd O comando atual.
 * @return 1 se a linha for nula, 2 se a linha for igual ao 
 * 			comando->here[0] (ou uma parte dele),
 *          0 caso contrário.
 */
static int	valid(char *line, t_command *cmd)
{
	if (!line)
		return (1);
	if (ft_strlen(line) == 1)
	{
		if (ft_strncmp(line, cmd->here[0], ft_strlen(cmd->here[0])) == 0)
			return (2);
	}
	else
	{
		if (ft_strncmp(line, cmd->here[0], ft_strlen(line) - 1) == 0)
			return (2);
	}
	return (0);
}

/**
 * Função responsável por receber a entrada do usuário para um here document.
 * 
 * @param cmd O comando atual sendo executado.
 */
void	here_doc_check(t_command *cmd)
{
	if (ft_strlen(cmd->red[0]) == 2)
		display_error(2, \
		"minishell: syntax error near unexpected token `newline'", false);
	else
		here_doc_input(cmd);
}

void	here_doc_input(t_command *cmd)
{
	char	*line;

	line = NULL;
	while (true)
	{
		write(0, "> ", 2);
		line = ft_get_next_line(0);
		if (valid(line, cmd) == 1)
		{
			here_doc_error(cmd->here[0]);
			break ;
		}
		else if (valid(line, cmd) == 2)
		{
			free(line);
			break ;
		}
		if (cmd->here[1] == NULL)
		{
			here_doc_expand_var(&line, cmd);
			write(shell()->here_doc_fd[1], line, ft_strlen(line));
		}
		free(line);
		line = NULL;
	}
}

/**
 * Função que remove as aspas de uma string.
 *
 * @param str A string da qual as aspas serão removidas.
 * @return A nova string sem as aspas, ou NULL se ocorrer 
 * 		um erro de alocação de memória.
 */
char	*remove_quotes(char *str)
{
	size_t	len;
	char	*new_str;

	len = ft_strlen(str);
	new_str = malloc(len - 1);
	if (new_str)
	{
		ft_memcpy(new_str, &str[1], len - 2);
		new_str[len - 2] = '\0';
	}
	return (new_str);
}

/**
 * Função que executa o redirecionamento de entrada usando o "here document".
 * 
 * @param cmd O comando a ser executado.
 * @return O descritor de arquivo para leitura do "here document".
 */
int	here_doc(t_command *cmd)
{
	pid_t	pid;

	shell()->in_here_doc = true;
	if (pipe(shell()->here_doc_fd) < 0)
		perror("pipe error");
	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_here_doc);
		if (cmd->here[0][0] == '"' && \
		cmd->here[0][ft_strlen(cmd->here[0]) - 1] == '"')
			cmd->here[0] = remove_quotes(cmd->here[0]);
		else if (cmd->here[0][0] == '\'' && \
			cmd->here[0][ft_strlen(cmd->here[0]) - 1] == '\'')
			cmd->here[0] = remove_quotes(cmd->here[0]);
		here_doc_check(cmd);
		signals_behavior();
		close_here_doc();
		exit(0);
	}
	wait(&pid);
	close(shell()->here_doc_fd[1]);
	shell()->in_here_doc = false;
	return (shell()->here_doc_fd[0]);
}
