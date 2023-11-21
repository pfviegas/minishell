/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:05:22 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/11 16:35:50 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Verifica se um caractere é um dígito decimal.
 *
 * A função `ft_isdigit` verifica se o caractere `c` é um dígito decimal (0-9).
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for um dígito decimal, 0 caso contrário.
 */

#include "libft.h"

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}
