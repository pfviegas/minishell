/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:12:40 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 12:12:40 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Localiza a última ocorrência de um caractere em uma string.
 *
 * A função ft_strrchr localiza a última ocorrência do caractere 'c' na 
 * string 'str'.
 *
 * @param str A string em que a busca será realizada.
 * @param c O caractere a ser encontrado.
 * @return Um ponteiro para a última ocorrência de 'c' em 'str', ou NULL se 
 * não for encontrado.
 */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)(str + i));
		i--;
	}
	return (NULL);
}
