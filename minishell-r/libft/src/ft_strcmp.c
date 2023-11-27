/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:18:39 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/24 14:18:39 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

// return diff between s1 and s2, greater if s1 is after
/**
 * Compara duas strings e 
 * retorna um valor inteiro que indica a diferença entre elas.
 *
 * @param s1 A primeira string a ser comparada.
 * @param s2 A segunda string a ser comparada.
 * @return Um valor inteiro negativo se s1 for menor que s2, 
 *         um valor inteiro positivo se s1 for maior que s2,
 *         ou zero se as strings forem iguais.
 */
int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			break;
		i++;
	}
	return (s1[i] - s2[i]);
}
