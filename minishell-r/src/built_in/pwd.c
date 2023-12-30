/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 11:10:06 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/30 14:33:29 by paulo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Imprime o diretório de trabalho atual.
 */
void	execute_pwd(void)
{
	char	cwd[PATH_MAX + 1];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd: ");
}

/**
 * Função para obter o diretório atual e atualizar a variável de ambiente PWD.
 * 
 * @param env Ponteiro para o array de strings com as variáveis de ambiente.
 */
void	get_pwd(void)
{
	char	buf[PATH_MAX + 1];

	if (shell()->pwd)
		free(shell()->pwd);
	getcwd(buf, sizeof(buf));
	shell()->pwd = ft_strdup(buf);
}
