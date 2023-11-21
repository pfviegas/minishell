/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:26:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/03 12:14:48 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Aplica uma função a cada caractere de uma string, gerando uma nova 
 * string com os resultados.
 *
 * A função ft_strmapi aplica a função 'f' a cada caractere da string 's' e gera
 * uma nova string com os resultados. A função 'f' recebe o índice do caractere 
 * e o próprio caractere como parâmetros e retorna o caractere resultante.
 *
 * @param s A string de entrada.
 * @param f A função a ser aplicada a cada caractere.
 * @return A nova string resultante.
 * @note É responsabilidade do chamador liberar a memória da nova string.
 */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;

	str = ft_strdup(s);
	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
		str[i] = f(i, str[i]);
	return (str);
}
