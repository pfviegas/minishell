/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:20:23 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/12 16:20:23 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Copia uma string para um buffer com limite de tamanho.
 *
 * A função ft_strlcpy copia a string 'src' para o buffer 'dest', com limite 
 * de tamanho 'size'.
 * Ela garante que a string resultante seja sempre nul-terminada e que o 
 * tamanho final não exceda 'size'.
 * 
 * @param dest O buffer de destino para a cópia da string.
 * @param src A string a ser copiada.
 * @param size O tamanho máximo do buffer 'dest', incluindo o espaço para o 
 *             caractere nul.
 * @return O comprimento da string de origem (não incluindo o caractere nul).
 */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	while (src[i] != '\0')
		i++;
	return (i);
}
