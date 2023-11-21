/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:06:27 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/11 16:27:00 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Verifica se um caractere é um caractere imprimível.
 *
 * A função `ft_isprint` verifica se o valor do caractere `c` é um caractere 
 * imprimível.
 * Caracteres imprimíveis são aqueles que possuem representação gráfica, ou 
 * seja, estão dentro do intervalo ASCII de 32 a 126 (inclusive), que inclui 
 * caracteres como letras, números, símbolos e caracteres especiais.
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for um caractere imprimível, 0 caso contrário.
 */

#include "libft.h"

int	ft_isprint(int c)
{
	return ((c >= 32 && c <= 126));
}
