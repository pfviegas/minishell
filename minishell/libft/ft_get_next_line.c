/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 13:29:37 by pviegas           #+#    #+#             */
/*   Updated: 2023/08/28 13:23:38 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Verifica se a linha deve ser liberada e retorna NULL se necessário.
 *
 * Esta função verifica se a linha deve ser liberada com base no número de 
 * bytes lidos.
 * Se `bytes` for 0 e a linha estiver vazia, a função libera a memória alocada 
 * para a linha e retorna NULL.
 *
 * @param line A linha a ser verificada.
 * @param bytes O número de bytes lidos.
 * @return A linha atualizada ou NULL se a linha deve ser liberada.
 */

static char	*chk_line(char *line, int bytes)
{
	if (bytes == 0 && *line == '\0')
	{
		free(line);
		return (NULL);
	}
	if (line == NULL)
	{
		line = malloc(1);
		if (!line)
			return (NULL);
		*line = '\0';
	}
	return (line);
}

/**
 * @brief Lê uma linha do arquivo referenciado pelo descritor de arquivo.
 *
 * Esta função lê uma linha do arquivo referenciado pelo descritor de 
 * arquivo `fd`.
 * A função lê os bytes do arquivo em um buffer temporário, concatenando-os 
 * na linha atual.
 * A função continua lendo até encontrar um caractere de nova linha ('\n') ou 
 * até que não haja mais bytes para ler do arquivo.
 *
 * @param fd O descritor de arquivo do arquivo a ser lido.
 * @param line A linha atual.
 * @return A linha atualizada com a leitura adicional do arquivo.
 *         A string é alocada dinamicamente e deve ser liberada pelo chamador.
 *         Retorna NULL se ocorrer um erro de leitura.
 */

static char	*read_line(int fd, char *line)
{
	char	*str;
	char	*tmp;
	int		bytes_read;

	str = (char *)malloc(BUFFER_SIZE + 1);
	if (!str)
		return (0);
	bytes_read = 1;
	line = chk_line(line, bytes_read);
	while (!ft_strchr(line, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, str, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(str);
			return (NULL);
		}
		str[bytes_read] = '\0';
		tmp = ft_strjoin(line, str);
		free(line);
		line = tmp;
	}
	free(str);
	line = chk_line(line, bytes_read);
	return (line);
}

/**
 * @brief Extrai a próxima linha da linha atual.
 *
 * Esta função extrai a próxima linha da linha atual e retorna uma nova string 
 * contendo a linha extraída.
 * A função remove a linha extraída da linha atual, atualizando-a para conter 
 * os bytes restantes.
 *
 * @param line A linha atual.
 * @return Uma nova string contendo a próxima linha extraída.
 *         A string é alocada dinamicamente e deve ser liberada pelo chamador.
 *         Retorna NULL se ocorrer um erro de alocação de memória.
 */

static char	*ft_next_line(char *line)
{
	char	*str;
	char	*str_f;
	int		nl_pos;

	if (!ft_strchr(line, '\n'))
		str_f = line + (ft_strlen(line) - 1);
	else
		str_f = ft_strchr(line, '\n');
	nl_pos = str_f - line + 1;
	str = (char *)malloc(nl_pos + 1);
	if (!str)
	{
		free(line);
		free(str);
		return (0);
	}
	ft_memmove(str, line, nl_pos);
	str[nl_pos] = '\0';
	ft_memmove(line, nl_pos + line, ft_strlen(line) - nl_pos + 1);
	return (str);
}

/**
 * @brief Lê uma linha de um arquivo descritor de arquivo.
 *
 * Esta função lê uma linha do arquivo referenciado pelo descritor de 
 * arquivo `fd`.
 * A função armazena a linha em uma string alocada dinamicamente e retorna 
 * um ponteiro para essa string. A função mantém o estado da leitura entre a
 * s chamadas, permitindo que linhas sucessivas sejam lidas do arquivo.
 *
 * @param fd O descritor de arquivo do arquivo a ser lido.
 * @return Um ponteiro para a linha lida do arquivo.
 *         A string é alocada dinamicamente e deve ser liberada pelo chamador.
 *         Retorna NULL se ocorrer um erro de leitura ou se não houver mais 
 *         linhas para ler.
 */

char	*ft_get_next_line(int fd)
{
	static char	*line;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_line(fd, line);
	if (!line)
		return (NULL);
	next_line = ft_next_line(line);
	if (!next_line)
		line = NULL;
	return (next_line);
}
