/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:24:55 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/12 16:24:55 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Concatena duas strings com limite de tamanho.
 *
 * A função ft_strlcat concatena a string 'src' à string 'dst', com limite 
 * de tamanho 'size'.
 * Ela garante que a string resultante seja sempre nul-terminada e que o 
 * tamanho final não exceda 'size'.
 * 
 * @param dst O buffer de destino para a concatenação das strings.
 * @param src A string a ser concatenada.
 * @param size O tamanho máximo do buffer 'dst', incluindo o espaço para o 
 *             caractere nul.
 * @return O comprimento total da string resultante após a concatenação.
 */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ii;
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dest_len = ft_strlen(dst);
	i = 0;
	ii = dest_len;
	if (dest_len < size - 1 && size > 0)
	{
		while (src[i] && (dest_len + i) < (size - 1))
		{
			dst[ii] = src[i];
			i++;
			ii++;
		}
		dst[ii] = 0;
	}
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + src_len);
}
