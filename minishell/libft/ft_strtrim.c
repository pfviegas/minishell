/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:53:35 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/14 10:53:35 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Remove os caracteres especificados no início e no final de uma string
 *
 * A função ft_strtrim remove os caracteres especificados em 'set' do início 
 * e do final da string 's1'.
 *
 * @param s1 A string a ser trimada.
 * @param set Os caracteres a serem removidos.
 * @return A string resultante após a remoção dos caracteres especificados.
 */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*start;
	char	*end;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = (char *)s1;
	while (*start && ft_strchr(set, *start))
		start++;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (end > start && ft_strchr(set, *end))
		end--;
	trimmed = ft_substr(start, 0, end - start + 1);
	return (trimmed);
}
