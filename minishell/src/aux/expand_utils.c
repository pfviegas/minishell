/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:53:40 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/22 15:19:25 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/**
 * @brief Prepares a string by splitting it into separate substrings based on quotes.
 * 
 * This function takes a string as input and splits it into separate substrings based on quotes.
 * It allocates memory for a matrix of strings and returns the matrix.
 * Each substring is stored in a separate element of the matrix.
 * The substrings are separated by single quotes ('') or double quotes ("").
 * 
 * @param str The input string to be prepared.
 * @return char** The matrix of prepared substrings.
 */

char	**split_by_quotes(char *str)
{
	int		i;
	int		j;
	int		size;
	int		sep;
	char	**matrix;

	i = -1;
	j = 0;
	sep = -1;
	size = 0;
	matrix = ft_calloc(1024, sizeof(char *));
	while (str[++i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && \
			(!sep || sep == str[i] || sep == -1))
			sep = (str[i]) * (sep != str[i]);
		if (++size && ((!sep && size) || ((str[i + 1] == '\'' \
			|| str[i + 1] == '\"') && sep < 0 && size)))
		{
			matrix[j++] = prepare_str(str, i, size);
			size = 0;
		}
	}
	*str = 0;
	return (matrix);
}

/**
 * @brief Prepares a substring from a given string.
 * 
 * This function takes a string, starting index, and size as input parameters.
 * It creates a new string and copies a substring of the given size from the original string,
 * starting from the specified index. The new string is then returned.
 * 
 * @param str The original string.
 * @param i The starting index.
 * @param size The size of the substring.
 * @return The prepared substring.
 */
char *prepare_str(char *str, int i, int size)
{
	char *res;
	int j;

	j = 0;
	i -= size - 1;
	res = ft_calloc(size + 1, 1);
	while (str[i] && j < size)
		res[j++] = str[i++];
	return res;
}
