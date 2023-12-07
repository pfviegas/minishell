/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:54:41 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/07 15:58:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		{
			msg = ft_strjoin(msg_aux, ": No such file or directory");
		}
		else
		{
			msg = ft_strjoin(path, ": command not found");
		}
	}
	else if (errno == 13)
	{
		msg = ft_strjoin(msg_aux, ": Permission denied");
	}
	else
	{
		msg = ft_strjoin(msg_aux, ": command not found");
	}
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
