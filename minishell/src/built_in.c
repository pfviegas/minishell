/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:59:31 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/08 13:38:14 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_built_in(t_commands *command)
{
	if (!ft_strncmp(command->content[0], "pwd", 3) || \
		!ft_strncmp(command->content[0], "cd", 2) || \
		!ft_strncmp(command->content[0], "echo", 4) || \
		!ft_strncmp(command->content[0], "env", 3) || \
		!ft_strncmp(command->content[0], "exit", 4) || \
		!ft_strncmp(command->content[0], "export", 6) || \
		!ft_strncmp(command->content[0], "unset", 5))
		return (1);
	else
		return (0);
}
