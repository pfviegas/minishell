/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:14:36 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/22 13:47:45 by pviegas          ###   ########.fr       */
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
	int		i;

	i = -1;
	while (shell()->env[++i])
	{
		temp = get_env_var_name(shell()->env[i]);
		if (ft_strcmp(env_var, temp) == 0)
		{
			rm_str_from_array(&shell()->env, i);
			free(temp);
			break ;
		}
		free(temp);
	}
}

/**
 * Função para executar o comando "unset".
 * Remove as variáveis de ambiente especificadas.
 *
 * @param cmd O array de strings contendo os argumentos do comando.
 */
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
