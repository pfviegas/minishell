/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:09:36 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 13:09:36 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Localiza a primeira ocorrência de um byte específico em uma área 
 * de memória.
 *
 * A função ft_memchr localiza a primeira ocorrência do byte 'c' na área de 
 * memória apontada por 's'.
 *
 * @param s Um ponteiro para a área de memória a ser verificada.
 * @param c O byte a ser localizado.
 * @param n O número de bytes a serem verificados.
 * @return Um ponteiro para a primeira ocorrência de 'c' em 's', ou NULL se 'c' 
 * não for encontrado.
 */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;

	p = s;
	while (n--)
	{
		if (*p == (unsigned char)c)
		{
			return ((void *)p);
		}
		p++;
	}
	return (NULL);
}
