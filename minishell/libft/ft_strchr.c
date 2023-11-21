/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:41 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 11:54:41 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Localiza a primeira ocorrência de um caractere em uma string.
 *
 * @param str A string na qual a busca será realizada.
 * @param c O caractere a ser localizado.
 * @return Um ponteiro para a primeira ocorrência de `c` em `str`, ou NULL se 
 * `c` não for encontrado.
 *
 * Esta função percorre a string `str` até encontrar o caractere `c` ou até 
 * encontrar o final da string (`'\0'`).
 * Se o caractere `c` for encontrado, a função retorna um ponteiro para essa 
 * posição em `str`.
 * Caso contrário, se o final da string for alcançado sem encontrar `c`, a 
 * função retorna NULL.
 *
 * @note A função não modifica a string de entrada `str`.
 */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	while (*str != (char)c)
	{
		if (!*str)
			return (0);
		str++;
	}
	return ((char *)str);
}
