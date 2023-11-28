/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:59:29 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 14:36:06 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Imprime o diretório de trabalho atual.
 */
void execute_pwd(void)
{
	char cwd[PATH_MAX + 1];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		perror("getcwd: Erro ao obter o diretório de trabalho atual");
}
//A constante PATH_MAX esta definida no <limits.h>
