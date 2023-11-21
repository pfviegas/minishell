/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:48 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/12 16:07:48 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Copia 'len' bytes da área de memória 'src' para a área de memória 
 * 'dst', tratando casos de sobreposição.
 *
 * A função ft_memmove copia 'len' bytes da área de memória 'src' para a área de
 * memória 'dst', tratando casos em que as áreas de memória podem se sobrepor.
 *
 * @param dst O ponteiro para a área de memória de destino.
 * @param src O ponteiro para a área de memória de origem.
 * @param len O número de bytes a serem copiados.
 * @return Um ponteiro para a área de memória de destino.
 */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int	i;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		i = (int)len - 1;
		while (i >= 0)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i--;
		}
	}
	else
	{
		i = 0;
		while (i < (int)len)
		{
			*(char *)(dst + i) = *(char *)(src + i);
			i++;
		}
	}
	return (dst);
}
