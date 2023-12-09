/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:59:29 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/09 16:35:27 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Imprime o diretório de trabalho atual.
 */
void	execute_pwd(void)
{
	char	cwd[PATH_MAX + 1];

//	verifica se o diretório de trabalho atual pode ser obtido
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
void	get_pwd(char ***env)
{
	char	buf[PATH_MAX + 1];
	char	*cmd;

//	obtem o diretorio atual
	getcwd(buf, sizeof(buf));
//	prepara a string de ambiente PWD
	cmd = ft_strjoin("PWD=", buf);
//	atualiza a variavel de ambiente PWD
	update_env(env, cmd);
//	verifica se a variavel de ambiente OLDPWD existe
	if (find_env_var(*env, "OLDPWD") == -1)
//		adiciona a variavel de ambiente OLDPWD ao array de variaveis de ambiente
		update_env(env, "OLDPWD");
	free(cmd);
}
