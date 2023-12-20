/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:43:49 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/20 17:40:47 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	close_here_doc(void)
{
	close(shell()->here_doc_fd[1]);
	close(shell()->here_doc_fd[0]);
	free_all(true, true, true, false);
}

/**
 * Função responsável por expandir variáveis em uma linha.
 * 
 * @param line A linha a ser expandida.
 */
void	here_doc_expand_var(char **line, t_command *cmd)
{
	char	*temp;
	int		i;

	temp = NULL;
	if (!(*line))
		return ;
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '$' && !(cmd->here[0][0] == '\'' || \
		cmd->here[0][0] == '"'))
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
	printf("\nWarning: heredoc on line 1 delimited by EOF \
	(wanted: \"%s\")\n", str);
	signals_behavior();
}

/**
 * Função para lidar com o sinal de here document.
 *
 * @param signal O sinal recebido.
 */
void	sig_here_doc(int signal)
{
	(void)signal;
	free_all(true, true, true, false);
	close(shell()->here_doc_fd[0]);
	close(shell()->here_doc_fd[1]);
	shell()->error = true;
	exit(EXIT_FAILURE);
}
