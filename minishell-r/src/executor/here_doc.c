/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:41:30 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/04 16:09:49 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função responsável por expandir variáveis em uma linha.
 * 
 * @param line A linha a ser expandida.
 */
void here_doc_expand_var(char **line)
{
	char *temp;
	
	int i;

	temp = NULL;
	if (!(*line))
		return;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$')
			expand_var(*line, &temp, &i);
		else
			add_char_string(&temp, (*line)[i]);
		i++;
	}
	free(*line);
	*line = temp;
}

/**
 * Função responsável por exibir um aviso quando ocorre um erro no heredoc.
 *
 * @param str A string delimitadora esperada.
 */
void	here_doc_error(char *str)
{
	printf("\nWarning: heredoc on line 1 delimited by EOF (wanted: \"%s\")\n", str);
	signals_behavior();
}

/**
 * Função para lidar com o sinal de here document.
 *
 * @param signal O sinal recebido.
 */
void sig_here_doc(int signal)
{
	(void)signal;
	free_all(true, true, true, false);
	close(shell()->here_doc_fd[0]);
	close(shell()->here_doc_fd[1]);
	shell()->error = true;
	exit(EXIT_FAILURE);
}

/**
 * Função que executa o redirecionamento de entrada usando o "here document".
 * 
 * @param cmd O comando a ser executado.
 * @return O descritor de arquivo para leitura do "here document".
 */
int here_doc(t_command *cmd)
{
	char *line;
	pid_t pid;
	int i;

	shell()->in_here_doc = true;
	if (pipe(shell()->here_doc_fd) < 0)
		perror("");
	pid = fork();
	i = 0;
	line = NULL;
//	verifica se o processo é o filho
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_here_doc);
		while (cmd->here && cmd->here[i])
		{
			while (true)
			{
				write(0, "> ", 2);
				line = ft_get_next_line(0);
				if (!line)
				{
					here_doc_error(cmd->here[i]);
					close(shell()->here_doc_fd[1]);
					close(shell()->here_doc_fd[0]);
					free_all(true, true, true, false);
					exit(-1);
				}
				if (!(ft_strncmp(line, cmd->here[i], ft_strlen(cmd->here[i]))))
				{
					free(line);
					break;
				}
				if (cmd->here[i + 1] == NULL)
				{
					here_doc_expand_var(&line);
					write(shell()->here_doc_fd[1], line, ft_strlen(line));
				}
				free(line);
				line = NULL;
			}
			i++;
		}
		signals_behavior();
		close(shell()->here_doc_fd[1]);
		close(shell()->here_doc_fd[0]);
		free_all(true, true, true, false);
		exit(0);
	}
	wait(&pid);
	close(shell()->here_doc_fd[1]);
	shell()->in_here_doc = false;
	return (shell()->here_doc_fd[0]);
}
