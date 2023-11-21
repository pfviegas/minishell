/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:50:07 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/20 13:55:49 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Esta funcao indica erro caso o comando seja um
diretorio e atualiza o respetivo exit code */
void	command_not_found(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 20);
	g_data.exit_status = 127;
	return ;
}

/* Esta funcao indica erro caso o comando seja um
diretorio e atualiza o respetivo exit code */
void	is_a_directory(char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, ": Is a directory\n", 17);
	g_data.exit_status = 126;
	return ;
}

// Define o erro caso o execve falhe,
void	error_handle(char *cmd)
{
	if (!ft_strchr(cmd, '/'))
		command_not_found(cmd);
	else if (ft_strchr(cmd, '/') && access(cmd, X_OK) == 0)
		is_a_directory(cmd);
	else if (access(cmd, F_OK) != 0)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": No such file or directory\n", 28);
		g_data.exit_status = 127;
		return ;
	}
	else if (access(cmd, X_OK))
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Permission denied\n", 20);
		g_data.exit_status = 126;
		return ;
	}
	else
	{
		perror("");
		g_data.exit_status = errno;
	}
}