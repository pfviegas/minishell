/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:07:42 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 14:07:42 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Localiza a primeira ocorrência de uma substring em uma string 
 * limitada.
 *
 * A função ft_strnstr localiza a primeira ocorrência da substring 'needle' 
 * na string 'haystack', com um limite máximo especificado por 'len'. 
 * A busca é feita de forma segura e retorna um ponteiro para a primeira 
 * ocorrência da substring na string ou NULL se a substring não for encontrada.
 *
 * @param haystack A string em que a busca será realizada.
 * @param needle A substring a ser encontrada.
 * @param len O número máximo de caracteres em 'haystack' a serem 
 * considerados na busca.
 * @return Um ponteiro para a primeira ocorrência de 'needle' em 'haystack', 
 * ou NULL se não for encontrada.
 */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (*haystack != '\0' && len-- >= needle_len)
	{
		if (ft_strncmp(haystack, needle, needle_len) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
