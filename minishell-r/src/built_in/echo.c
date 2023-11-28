/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:15:51 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 13:43:32 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Salta as flags do comando echo e retorna a posição do próximo argumento.
 *
 * @param cmd   O array de strings contendo os argumentos do comando echo.
 * @param flag  Um ponteiro para uma variável booleana que indica se a 
 *              flag "-n" foi encontrada.
 * @return      A posição do próximo argumento após as flags.
 */
int skip_echo_flags(char **cmd, bool *flag)
{
	int i;
	int j;

	i = 0;
	while (cmd[++i])
	{
		if (cmd[i][0] != '-')
			return (i);
		j = 1;
		if (cmd[i][1] == '\0')
			return (i);
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		*flag = true;
	}
	return (i);
}

/**
 * Função para executar o comando "echo".
 * 
 * @param cmd O array de strings contendo os argumentos do comando.
 */
void execute_echo(char **cmd)
{
	bool flag;
	int i;

	flag = false;
	if (!cmd[1])
	{
		printf("\n");
		return;
	}
	i = skip_echo_flags(cmd, &flag) - 1;
	while (cmd[++i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
	}
	if (!flag)
		printf("\n");
	shell()->exit_code = 0;
}
