/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:31:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 12:03:52 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Verifica se o caminho especificado é um diretório e exibe um erro caso seja.
 * 
 * @param path O caminho a ser verificado.
 */
void error_before_execute(char *path)
{
	struct stat st;
	
	if (stat(path, &st) == -1)
		return;
	if (S_ISDIR(st.st_mode) && path && (!ft_strncmp("./", path, 2) || path[0] == '/'))
	{
		display_error(126, " É um diretório", true);
		free_all(1, 1, 1, 1);
	}
}

/**
 * Encontra o índice da variável de ambiente "PATH" em um array de strings.
 *
 * @param envp  O array de strings contendo as variáveis de ambiente.
 * @return      O índice da variável "PATH" se encontrada, \
 *              caso contrário retorna -1.
 */
int find_env_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (i);
		i++;
	}
	return (-1);
}

/**
 * Função que encontra o caminho completo de um comando no ambiente.
 *
 * @param envp O array de strings contendo as variáveis de ambiente.
 * @param cmd  O comando a ser encontrado.
 * @return    O caminho completo do comando, ou NULL se não for encontrado.
 */
char	*find_path(char **envp, char *cmd)
{
	int		index;
	char	*path;
	char	*temp;
	char	**paths;
	int		i;

	path = NULL;
	temp = NULL;
	paths = NULL;
	if (!envp || !envp[0])
		return (ft_strdup(cmd));
	index = find_env_path(envp);
	if (index == -1)
		return (NULL);
	path = &envp[index][6];
	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(temp, cmd);
		if (access(path, F_OK) != -1)
		{
			free(temp);
			free_array(&paths);
			return (path);
		}
		free(temp);
		free(path);
		i++;
	}
	free_array(&paths);
	return (ft_strdup(cmd));
}
