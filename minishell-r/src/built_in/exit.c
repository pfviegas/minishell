/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:37:59 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/05 11:22:17 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função responsável por executar o comando "exit" no shell.
 * 
 * @param cmd O array de strings contendo os argumentos do comando.
 */
void execute_exit(char **cmd)
{
	int		i;
	char	*msg;
	char	*msg_aux;

	printf("exit\n");
	i = -1;
	while (cmd && cmd[1] && cmd[1][++i])
	{
		if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
			continue;
		else if (!ft_isdigit(cmd[1][i]))
		{
			msg_aux = ft_strjoin("minishell: exit: ", cmd[1]);
			msg = ft_strjoin(msg_aux, ": numeric argument required");
			free(msg_aux);
			display_error(2, msg, true);
			free(msg);
			break;
		}
		else if (cmd[1][i + 1] == '\0' && cmd[2])
		{
			display_error(1, "minishell: exit: too many arguments", true);
			return;
		}
		else if (cmd[1][i + 1] == '\0')
		{	
			shell()->exit_code = ft_atoi(cmd[1]);
		}
	}
	shell()->prompt = false;
}
