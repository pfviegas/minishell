/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 10:45:19 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/14 10:45:19 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Creates a substring from a given string.
 *
 * The ft_substr() function creates a new string that is a substring of the
 * input string 's'. The substring begins at the index 'start' and has a length
 * of 'len'. The substring is allocated dynamically and should be freed by the
 * caller when no longer needed.
 *
 * @param s The input string.
 * @param start The starting index of the substring.
 * @param len The length of the substring.
 *
 * @return The substring or NULL if allocation fails or invalid parameters are
 * provided. The returned substring must be freed by the caller.
 */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len)
		return (ft_strdup(""));
	s_len = s_len - start;
	if (s_len > len)
		s_len = len;
	substr = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!substr)
	{
		free(substr);
		return (NULL);
	}
	ft_memcpy(substr, s + start, s_len);
	substr[s_len] = '\0';
	return (substr);
}
