/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:56:44 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/11 16:24:35 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Divide uma string em substrings com base em um caractere delimitador.
 *
 * A função ft_split divide a string 's' em substrings usando o caractere 
 * delimitador 'c'.
 *
 * @param s A string a ser dividida.
 * @param c O caractere delimitador usado para dividir a string.
 * @return Um ponteiro para uma matriz de strings contendo as substrings r
 * esultantes da divisão.
 * @note A matriz retornada e a própria string de entrada devem ser liberadas 
 * quando não forem mais necessárias.
 */

#include "libft.h"

// count the number of words
static size_t	count_words(const char *s, char c)
{
	size_t	words;
	int		in_word;

	words = 0;
	in_word = 0;
	while (*s)
	{
		if (in_word && *s == c)
		{
			in_word = 0;
		}
		else if (in_word == 0 && *s != c)
		{
			in_word = 1;
			words++;
		}
		s++;
	}
	return (words);
}

// get the next word
static char	*next_word(const char **s, char c)
{
	const char	*start;
	char		*word;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	word = ft_substr(start, 0, *s - start);
	if (!word)
	{
		free(word);
		return (NULL);
	}
	if (**s)
		(*s)++;
	return (word);
}

// split the string in words 
char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		n_words;
	char		**words;
	const char	*p;

	p = s;
	n_words = count_words(s, c);
	words = (char **)malloc(sizeof(char *) * (n_words + 1));
	if (!s || !words)
		return (NULL);
	i = 0;
	while (i < n_words)
	{
		words[i] = next_word(&p, c);
		if (!words[i])
		{
			while (i--)
				free(words[i]);
			free(words);
			return (NULL);
		}
		i++;
	}
	words[i] = NULL;
	return (words);
}
