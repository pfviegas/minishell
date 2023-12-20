/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:37:59 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/20 16:22:32 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	handle_numeric_error(char *cmd)
{
	char	*msg_aux;
	char	*msg;

	msg_aux = ft_strjoin("minishell: exit: ", cmd);
	msg = ft_strjoin(msg_aux, ": numeric argument required");
	free(msg_aux);
	display_error(2, msg, true);
	free(msg);
}

/**
 * Função responsável por executar o comando "exit" no shell.
 * 
 * @param cmd O array de strings contendo os argumentos do comando.
 */
void	execute_exit(char **cmd)
{
	int		i;

	printf("exit\n");
	i = -1;
	while (cmd && cmd[1] && cmd[1][++i])
	{
		if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
			continue ;
		if (!ft_isdigit(cmd[1][i]))
		{
			handle_numeric_error(cmd[1]);
			break ;
		}
		if (cmd[1][i + 1] == '\0' && cmd[2])
		{
			display_error(1, "minishell: exit: too many arguments", true);
			return ;
		}
		if (cmd[1][i + 1] == '\0')
			shell()->exit_code = ft_atoi(cmd[1]);
	}
	shell()->prompt = false;
}
