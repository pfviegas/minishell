/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:15:51 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/08 15:58:23 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_args(char **str, size_t i)
{
	size_t	j;

	j = 0;
	while (str[j])
		j++;
	while (str[i])
	{
		if ((i + 1) != j)
			printf("%s ", str[i]);
		else
			printf("%s", str[i]);
		i++;
	}
}

// Replica o comando echo do bash com a opcao -n que remove a newline
void	execute_echo(t_commands **command)
{
	int	flag;

	flag = 0;
//	close_fds(command, 1);
	if ((*command)->content[1] && (*command)->content[1][0] \
		== '-' && (*command)->content[1][1] == 'n')
		flag = 1;
	if (flag == 0)
	{
		print_args((*command)->content, 1);
		printf("\n");
	}
	else if (flag == 1)
		print_args((*command)->content, 2);

	g_data.exit_status = 0;
}