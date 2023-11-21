/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:04:02 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 13:04:02 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compara duas strings de forma segura até um tamanho especificado.
 *
 * A função ft_strncmp compara os caracteres das strings 'str1' e 'str2' até 
 * um tamanho máximo especificado por 'n'. A comparação é feita de forma segura, 
 * evitando acessar * além dos limites das strings. A função retorna um valor 
 * inteiro indicando a ordem lexicográfica das strings.
 *
 * @param str1 A primeira string a ser comparada.
 * @param str2 A segunda string a ser comparada.
 * @param n O número máximo de caracteres a serem comparados.
 * @return Um valor inteiro menor, igual ou maior que zero, indicando se 'str1' é
 *         menor, igual ou maior que 'str2', respectivamente.
 */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (str1[i] == str2[i]) && (str1[i] != '\0')
		&& (str2[i] != '\0'))
	{
		i++;
	}
	if (i == n)
	{
		return (0);
	}
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}
