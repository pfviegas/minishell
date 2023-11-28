/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:20:44 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 14:53:14 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função para executar o comando "unset" que remove variáveis de ambiente.
 *
 * @param cmd O comando e seus argumentos.
 */
void execute_unset(char **cmd)
{
	char *temp;
	int i;
	int array_index;

	if (!cmd || ft_strcmp(cmd[0], "unset") != 0)
		return;
	if (cmd[1])
	{
		i = 0;
		while (cmd[++i])
		{
			array_index = -1;
			while (shell()->env[++array_index])
			{
				temp = get_env_var_name(shell()->env[array_index]);
				if (ft_strcmp(cmd[i], temp) == 0)
				{
					rm_str_from_array(&shell()->env, array_index);
					free(temp);
					break;
				}
				free(temp);
			}
		}
	}
}
