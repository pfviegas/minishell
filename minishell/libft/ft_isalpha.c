/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:05:00 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/03 11:58:11 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Verifica se um caractere é uma letra.
 *
 * A função `ft_isalpha` verifica se o caractere `c` é uma letra do alfabeto.
 * Letras são definidas como caracteres maiúsculos (A-Z) e minúsculos (a-z).
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for uma letra, 0 caso contrário.
 */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
