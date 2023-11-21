/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:00:15 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/12 16:00:15 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Copia 'n' bytes da área de memória 'src' para a área de memória 'dest'
 *
 * A função ft_memcpy copia 'n' bytes da área de memória 'src' para a área 
 * de memória 'dest'. As áreas de memória não devem se sobrepor.
 *
 * @param dest O ponteiro para a área de memória de destino.
 * @param src O ponteiro para a área de memória de origem.
 * @param n O número de bytes a serem copiados.
 * @return Um ponteiro para a área de memória de destino.
 */

#include "libft.h"

// copies 'n' bytes from 'src' to 'dest'
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}
