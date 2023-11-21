/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:15:25 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 13:15:25 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Compara os primeiros 'n' bytes de duas áreas de memória.
 *
 * A função ft_memcmp compara os primeiros 'n' bytes das áreas de memória 
 * apontadas por 'str1' e 'str2'.
 *
 * @param str1 Um ponteiro para a primeira área de memória a ser comparada.
 * @param str2 Um ponteiro para a segunda área de memória a ser comparada.
 * @param n O número de bytes a serem comparados.
 * @return Um valor inteiro negativo se 'str1' for menor que 'str2', um valor 
 * inteiro positivo se 'str1' for maior que 'str2' ou 0 se forem iguais.
 */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const unsigned char	*p1;
	const unsigned char	*p2;

	p1 = str1;
	p2 = str2;
	while (n--)
	{
		if (*p1 != *p2)
			return (*p1 - *p2);
		p1++;
		p2++;
	}
	return (0);
}
