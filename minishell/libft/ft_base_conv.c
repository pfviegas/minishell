/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 16:38:28 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/03 11:57:49 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converte um número inteiro para uma string representando sua forma 
 * na base especificada.
 *
 * Esta função converte um número inteiro não assinado para uma string que 
 * representa o número na base especificada. A base é fornecida como uma string 
 * contendo os caracteres que representam os dígitos da base 
 * (por exemplo, "0123456789ABCDEF" para base hexadecimal).
 *
 * @param n O número inteiro não assinado a ser convertido.
 * @param base A string que contém os dígitos da base.
 * @return A string resultante da conversão do número para a base especificada.
 *         A string é alocada dinamicamente e deve ser liberada pelo chamador.
 *         Retorna NULL em caso de falha na alocação de memória.
 */

#include "libft.h"

static size_t	ft_len(unsigned long long n, char *base)
{
	size_t				len;
	unsigned long long	base_len;

	len = 1;
	base_len = ft_strlen(base);
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

char	*ft_base_conv(unsigned long long n, char *base)
{
	char	*str;
	int		num_len;
	int		base_len;

	num_len = ft_len(n, base);
	base_len = ft_strlen(base);
	str = ft_calloc((num_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (num_len)
	{
		num_len = num_len - 1;
		str[num_len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
