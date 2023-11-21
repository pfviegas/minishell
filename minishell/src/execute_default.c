/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_default.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:08:32 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/20 13:55:04 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Executa os comandos default (not built in)
void	execute_default(t_commands **command)
{
	char	**our_env;

	our_env = lst_to_arr(g_data.env);
	close_fds(command, 1);
	if (execve((*command)->path, (*command)->content, our_env) == -1)
		error_handle((*command)->content[0]);
	close(0);
	close(1);
	lst_first(command);
	free_str_array(&our_env);
	free_env(&g_data.env);
	free_vars();
	exit(g_data.exit_status);
}