/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:32:50 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 14:32:50 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Duplica uma string.
 *
 * A função ft_strdup cria uma cópia da string 's1'.
 *
 * @param s1 A string a ser duplicada.
 * @return Um ponteiro para a nova string duplicada, ou NULL em caso de falha 
 * de alocação de memória.
 * @note A nova string retornada deve ser liberada quando não for mais 
 * necessária.
 */

#include "libft.h"
// doubles a string
char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*str;

	len = 0;
	while (s1[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		free(str);
		return (NULL);
	}
	len = 0;
	while (s1[len])
	{
		str[len] = s1[len];
		len++;
	}
	str[len] = '\0';
	return (str);
}
