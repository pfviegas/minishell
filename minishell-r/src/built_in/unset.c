/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:20:44 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/01 14:41:04 by pviegas          ###   ########.fr       */
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
	char	*temp;
	int		i;
	int		array_index;

//PFV
//	if (!cmd || ft_strcmp(cmd[0], "unset") != 0)
//		return;
	if (cmd[1])
	{
		i = 0;
//		Percorre o array de argumentos
		while (cmd[++i])
		{
			array_index = -1;
//			Percorre o array de variáveis de ambiente
			while (shell()->env[++array_index])
			{
//				Obtém o nome da variável de ambiente
				temp = get_env_var_name(shell()->env[array_index]);
//				Verifica se o nome da variável de ambiente é igual ao argumento
				if (ft_strcmp(cmd[i], temp) == 0)
				{
//					Remove a variável de ambiente
					rm_str_from_array(&shell()->env, array_index);
					free(temp);
					break;
				}
				free(temp);
			}
		}
	}
}
