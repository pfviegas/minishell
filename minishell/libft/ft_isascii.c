/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:06:04 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/12 16:06:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Verifica se um caractere é um caractere ASCII.
 *
 * A função `ft_isascii` verifica se o valor do caractere `c` está dentro do
 * intervalo ASCII válido, ou seja, de 0 a 127 (inclusive).
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for um caractere ASCII, 0 caso contrário.
 */

#include "libft.h"

int	ft_isascii(int c)
{
	return ((c >= 0 && c <= 127));
}
