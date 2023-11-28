/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:37:59 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 16:29:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_exit(char **cmd)
{
	int	i;
	int	code;

	code = 0;
//PFV
//	if (!cmd || ft_strcmp(cmd[0], "exit"))
//		return ;
	printf("exit\n");
	i = -1;
	while (cmd && cmd[1] && cmd[1][++i])
	{
		if (i == 0 && (cmd[1][0] == '+' || cmd[1][0] == '-'))
			continue ;
		else if (!ft_isdigit(cmd[1][i]))
		{
			write(STDERR_FILENO, " numeric argument required\n", 27);
			code = 2;
			break ;
		}
		else if (cmd[1][i + 1] == '\0' && cmd[2])
		{
			write(STDERR_FILENO, " too many arguments\n", 20);
			code = 1;
		}
		else if (cmd[1][i + 1] == '\0')
			code = ft_atoi(cmd[1]);
	}
	shell()->exit_code = code;
	shell()->prompt = false;
}