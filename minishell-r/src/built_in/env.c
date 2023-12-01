/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:41:02 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/01 14:19:35 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Recupera o nome da variável de ambiente a partir de uma string fornecida.
 *
 * Esta função procura pela primeira ocorrência do caractere '=' na string 
 * de entrada e retorna uma substring contendo todos os caracteres antes dele.
 *
 * @param str A string de entrada contendo a variável de ambiente.
 * @return Uma substring contendo o nome da variável de ambiente.
 */
char	*get_env_var_name(char *str)
{
	int		i;

	i = 0;
	while (str && str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

/**
 * Função para executar o comando "env".
 * 
 * @param env O array de strings com as variáveis de ambiente.
 */
void	execute_env(char **env)
{
	int		i;

	i = 0;
//	Exibe todas as variáveis de ambiente
	while (env && env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

//PFV
/*
void	execute_env(char **env)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
//	Exibe todas as variáveis de ambiente
	while (env && env[++i])
	{
//		Recupera o nome da variável de ambiente
		temp = get_env_var_name(env[i]);
		j = 0;
		while (temp[j])
			j++;
		if (env[i][j] == '=')
			printf("%s\n", env[i]);
		free(temp);
	}
}
*/
