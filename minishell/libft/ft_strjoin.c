/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:52:12 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/14 10:52:12 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Concatena duas strings em uma nova string.
 *
 * A função ft_strjoin concatena as strings 's1' e 's2' em uma nova string,
 * alocada dinamicamente, e retorna um ponteiro para a nova string resultante.
 *
 * @param s1 A primeira string a ser concatenada.
 * @param s2 A segunda string a ser concatenada.
 * @return Um ponteiro para a nova string resultante, ou NULL em caso de falha 
 * na alocação de memória.
 */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new_str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, len1);
	ft_memcpy(new_str + len1, s2, len2);
	new_str[len1 + len2] = '\0';
	return (new_str);
}
