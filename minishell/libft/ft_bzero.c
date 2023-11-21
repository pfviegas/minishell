/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:07:26 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/12 16:07:26 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Preenche um bloco de memória com zeros.
 *
 * A função `ft_bzero` preenche os primeiros `n` bytes do bloco de memória
 * apontado por `s` com zeros.
 *
 * @param s O ponteiro para o bloco de memória a ser preenchido com zeros.
 * @param n O número de bytes a serem preenchidos com zeros.
 */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
