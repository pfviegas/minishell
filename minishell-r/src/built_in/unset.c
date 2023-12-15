/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:20:44 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/15 11:17:35 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função para remover uma variável de ambiente específica 
 * do array de variáveis de ambiente.
 *
 * @param env_var A variável de ambiente a ser removida.
 */
void	unset_single_env(char *env_var)
{
	char	*temp;
	int		array_index;

	array_index = -1;
	while (shell()->env[++array_index])
	{
		if (env_var[0] != '_')
		{
			temp = get_env_var_name(shell()->env[array_index]);
			if (ft_strcmp(env_var, temp) == 0)
			{
				rm_str_from_array(&shell()->env, array_index);
				free(temp);
				break ;
			}
			free(temp);
		}
	}
}

// Função principal para executar unset para várias variáveis de ambiente
void	execute_unset(char **cmd)
{
	int	i;

	if (cmd[1])
	{
		i = 0;
		while (cmd[++i])
		{
			unset_single_env(cmd[i]);
		}
	}
}
