/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:05:44 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/03 11:56:25 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Verifica se um caractere é alfanumérico.
 *
 * A função `ft_isalnum` verifica se o caractere `c` é um caractere alfanumérico.
 * Caracteres alfanuméricos são letras maiúsculas e minúsculas (A-Z, a-z) e
 * dígitos (0-9).
 *
 * @param c O caractere a ser verificado.
 * @return 1 se o caractere for alfanumérico, 0 caso contrário.
 */

#include "libft.h"

int	ft_isalnum(int c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9'));
}
