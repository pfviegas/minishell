/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:12:39 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 14:12:39 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/**
 * @brief Converte uma string para um valor inteiro.
 *
 * A função `ft_atoi` converte a string `str` em um valor inteiro.
 *
 * @param str A string a ser convertida.
 * @return O valor inteiro convertido.
 */
#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (sign * res);
}
