/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:10 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/12 16:07:10 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Preenche uma área de memória com um valor específico.
 *
 * A função ft_memset preenche os primeiros 'num' bytes da área de memória 
 * apontada por 'ptr' com o valor 'value'.
 *
 * @param ptr O ponteiro para a área de memória a ser preenchida.
 * @param value O valor a ser colocado em cada byte.
 * @param num O número de bytes a serem preenchidos.
 * @return Um ponteiro para a área de memória preenchida.
 */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t	i;

	i = 0;
	while (i < num)
	{
		((unsigned char *)ptr)[i] = value;
		i++;
	}
	return (ptr);
}
