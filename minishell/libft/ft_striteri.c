/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:37:42 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/03 12:10:36 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Aplica uma função a cada caractere de uma string.
 *
 * A função ft_striteri aplica a função 'f' a cada caractere da string 's',
 * passando o índice do caractere como primeiro argumento para 'f'.
 *
 * @param s A string a ser percorrida.
 * @param f A função a ser aplicada a cada caractere da string.
 * @return Sem retorno.
 * @note A função 'f' deve ter o seguinte protótipo: 
 *       void f(unsigned int index, char *c);
 */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
