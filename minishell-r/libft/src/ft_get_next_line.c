/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:55:26 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/04 16:00:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

/**
 * Calcula o tamanho de uma string, excluindo o caractere de nova linha ('\n').
 *
 * @param str    A string de entrada.
 * @return       O tamanho da string, excluindo o caractere de nova linha.
 */
size_t str_len(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != '\n')
		i++;
	return (i + (str[i] == '\n'));
}

/**
 * Função que concatena duas strings e retorna o resultado.
 *
 * @param line    A primeira string a ser concatenada.
 * @param stash   A segunda string a ser concatenada.
 * @return        A string resultante da concatenação de line e stash.
 */
static char	*ft_join(char *line, char *stash)
{
	char	*ret;
	size_t	i;

	ret = (char *)malloc((str_len(line) + str_len(stash)) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (line && line[++i])
		ret[i] = line[i];
	i += (!line);
	free(line);
	while (*stash)
	{
		ret[i++] = *stash;
		if (*stash++ == '\n')
			break ;
	}
	ret[i] = '\0';
	return (ret);
}

/**
 * Limpa o próximo caractere de nova linha ('\n').
 * 
 * @param stash   A string a ser verificada e modificada.
 * @return        1 se um caractere de nova linha foi encontrado e removido, 
 *                0 caso contrário.
 */
static int ft_nextclean(char *stash)
{
	int nl_flag = 0;
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (stash[i])
	{
		if (stash[i] == '\n')
		{
			nl_flag = 1;
			stash[i++] = 0;
			break;
		}
		stash[i++] = 0;
	}
	if (nl_flag)
	{
		while (stash[i])
		{
			stash[j++] = stash[i];
			stash[i++] = 0;
		}
	}
	return (nl_flag);
}

/**
 * Função para ler a próxima linha de um arquivo.
 *
 * Lê a próxima linha do arquivo especificado pelo descritor de arquivo (fd).
 * Armazena o conteúdo lido em um buffer estático (stash) e 
 * retorna a linha lida como uma string.
 * Se ocorrer um erro na leitura ou se o tamanho do buffer for menor que 1, 
 * a função retorna NULL.
 *
 * @param fd    O descritor de arquivo do qual ler a próxima linha.
 * @return      A próxima linha lida do arquivo ou NULL em caso de erro.
 */
char	*ft_get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE + 1];
	char		*line;
	int 		i;
	
	i = 0;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		while (stash[i])
			stash[i++] = 0;
		return (NULL);
	}
	line = NULL;
	while (*stash || read(fd, stash, BUFFER_SIZE) > 0)
	{
		line = ft_join(line, stash);
		if (ft_nextclean(stash))
			break ;
	}
	return (line);
}
