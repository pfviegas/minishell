/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:31:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/05 14:32:58 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Função para verificar e liberar memória dos caminhos
static char	*check_and_free_paths(char **paths, char *cmd)
{
	if (access(cmd, F_OK) != -1)
	{
		free_array(&paths);
		return (cmd);
	}
	free(cmd);
	return (NULL);
}

/**
 * Constrói o caminho completo para um comando, 
 * concatenando o diretório e o comando.
 *
 * @param dir   O diretório onde o comando está localizado.
 * @param cmd   O nome do comando.
 * @return      O caminho completo para o comando.
 */
static char	*build_full_path(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

/**
 * Verifica se o caminho especificado é um diretório e exibe um erro caso seja.
 * 
 * @param path O caminho a ser verificado.
 */
void	check_dir(char *path)
{
	struct stat	st;
	char		*msg;
	char		*msg_aux;

	if (stat(path, &st) == -1)
		return ;
	if (S_ISDIR(st.st_mode) && path && 
		(!ft_strncmp("./", path, 2) || path[0] == '/'))
	{
		msg_aux = ft_strjoin("minishell: ", path);
		msg = ft_strjoin(msg_aux, ": Is a directory");
		free(path);
		free(msg_aux);
		display_error(126, msg, true);
		free(msg);
		free_all(true, true, true, true);
	}
}

/**
 * Encontra o índice da variável de ambiente "PATH" em um array de strings.
 *
 * @param envp  O array de strings contendo as variáveis de ambiente.
 * @return      O índice da variável "PATH" se encontrada, \
 *              caso contrário retorna -1.
 */
int	find_env_path(char **envp)
{
	int	i;

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
 * @return     O caminho completo do comando, ou NULL se não for encontrado.
 */
char	*find_path(char **envp, char *cmd)
{
	int		index;
	char	*path;
	char	**paths;
	char	*full_path;
	char	*result;

	if (!envp || !envp[0])
		return (ft_strdup(cmd));
	index = find_env_path(envp);
	if (index == -1)
		return (NULL);
	path = &envp[index][6];
	paths = ft_split(path, ':');
	index = -1;
	while (paths[++index])
	{
		full_path = build_full_path(paths[index], cmd);
		result = check_and_free_paths(paths, full_path);
		if (result)
			return (result);
	}
	free_array(&paths);
	return (ft_strdup(cmd));
}
