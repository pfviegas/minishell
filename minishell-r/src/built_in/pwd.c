/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paulo <paulo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:59:29 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/15 10:24:47 by paulo            ###   ########.fr       */
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
void	get_pwd(char ***env)
{
	char	buf[PATH_MAX + 1];
	char	*cmd;

	getcwd(buf, sizeof(buf));
	cmd = ft_strjoin("PWD=", buf);
	update_env(env, cmd);
	if (find_env_var(*env, "OLDPWD") == -1)
		update_env(env, "OLDPWD");
	free(cmd);
}
