/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:12:04 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/21 14:49:41 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc_input(t_command *cmd)
{
	int		i;
	char	*line;

	i = -1;
	line = NULL;
	while (cmd->here && cmd->here[++i])
	{
		while (true)
		{
			write(0, "> ", 2);
			line = ft_get_next_line(0);
			if (!(ft_strncmp(line, cmd->here[i], ft_strlen(cmd->here[i]))))
			{
				free(line);
				break ;
			}
			if (cmd->here[i + 1] == NULL)
			{
				here_doc_expand_var(&line, cmd);
				write(shell()->here_doc_fd[1], line, ft_strlen(line));
			}
			free(line);
			line = NULL;
		}
	}
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_here_doc);
	if (pid == 0)
	{
		here_doc_input(cmd);
		signals_behavior();
		close_here_doc();
		exit(0);
	}
	wait(&pid);
	close(shell()->here_doc_fd[1]);
	shell()->in_here_doc = false;
	return (shell()->here_doc_fd[0]);
}
