/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:59:29 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/08 15:58:23 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Obtem o diretório de trabalho atual. 
// Recebe como argumentos o buffer cwd para armazenar o diretório atual 
// e o tamanho máximo do buffer. cwd (current working directory)
void	execute_pwd(t_commands **command)
{
	char	cwd[PATH_MAX];
	int		i;

//	close_fds(command, 1);
	i = 0;
	if ((*command)->content[1])
	{
		while((*command)->content[1][i])
		{
			if (!ft_isspace((char)(*command)->content[1][i++]))
			{
				write(2, "pwd: too many arguments\n", 24);
				return ;
			}
		}
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		perror("Error getting current working directory");
		return ;
	}
	g_data.exit_status = 0;
}

//A constante PATH_MAX esta definida no <limits.h>