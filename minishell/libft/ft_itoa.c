/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:18:22 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/14 13:18:24 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Calcula o número de dígitos em um inteiro.
 *
 * A função `int_len` calcula o número de dígitos no inteiro `n`.
 *
 * @param n O inteiro a ser calculado o número de dígitos.
 * @return O número de dígitos no inteiro `n`.
 */

#include "libft.h"

static size_t	int_len(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		len;
	long int	num;

	num = n;
	len = int_len(n);
	if (n < 0)
	{
		num *= -1;
		len++;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len) = 0;
	while (len--)
	{
		*(str + len) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str) = '-';
	return (str);
}
