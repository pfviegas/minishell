/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:54:08 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/21 11:39:43 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Procura a variavel ambiente PATH e confirma com o comando access se o
// o comando a executar existe ou nao, caso exista retorna o caminho
char	*get_cmd_path(char **env, char **cmd)
{
	char	**str_array;
	char	*temp;
	char	*cmd_path;
	int		i;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		return (ft_strdup(cmd[0]));
	str_array = ft_split(env_search_str(env, "PATH"), ':');
	cmd_path = ft_strjoin("/", cmd[0]);
	while (str_array[i])
	{
		temp = ft_strjoin(str_array[i], cmd_path);
		if (access(temp, X_OK) == 0)
		{
			free(cmd_path);
			cmd_path = temp;
			free(temp);
			break ;
		}
		free(temp);
		i++;
	}
	free_str_array(&str_array);
	return (cmd_path);
}
