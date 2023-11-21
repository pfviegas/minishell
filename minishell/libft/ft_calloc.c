/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:26:34 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 14:26:34 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Aloca e preenche uma região de memória com zeros.
 *
 * A função `ft_calloc` aloca uma região de memória com espaço para `count`
 * elementos de tamanho `size`. Em seguida, preenche essa região de memória com
 * zeros.
 *
 * @param count O número de elementos a serem alocados.
 * @param size O tamanho de cada elemento em bytes.
 * @return Um ponteiro para a região de memória alocada e preenchida com zeros,
 *         ou NULL em caso de falha na alocação de memória.
 */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, count * size);
	return (ptr);
}
