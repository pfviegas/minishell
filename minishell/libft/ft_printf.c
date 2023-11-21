/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:55:51 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/11 16:31:08 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Imprime uma sequência formatada no stdout.
 *
 * A função `ft_printf` permite imprimir uma sequência formatada no stdout. 
 * A sequência formatada é composta por caracteres de texto e especificadores 
 * de formato, que são substituídos pelos valores correspondentes passados como 
 * argumentos.
 *
 * @param format A sequência de formato a ser impressa.
 * @param ... Os argumentos correspondentes aos especificadores de formato.
 * @return O número total de caracteres impressos, ou 0 se ocorrer um erro.
 *
 * @remarks
 * - A função suporta os seguintes especificadores de formato: 
 *     'd', 'i', 'c', 's', 'p', 'u', 'x', 'X', '%'.
 *
 * @see ft_check_format
 */

#include "libft.h"

static void	ft_check_format(va_list args, char spec, size_t *counter)
{
	if (spec == 'd' || spec == 'i')
		ft_putnbr_ct(va_arg(args, int), counter);
	else if (spec == 'c')
		ft_putchar_ct(va_arg(args, int), counter);
	else if (spec == 's')
		ft_putstr_ct(va_arg(args, char *), counter);
	else if (spec == 'p')
		ft_putptr_ct(va_arg(args, void *), counter);
	else if (spec == 'u')
		ft_putuint_ct(va_arg(args, unsigned int), counter);
	else if (spec == 'x')
		ft_puthexl_ct(va_arg(args, unsigned int), counter);
	else if (spec == 'X')
		ft_puthexh_ct(va_arg(args, unsigned int), counter);
	else if (spec == '%')
		ft_putchar_ct(spec, counter);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	size_t	counter;

	if (!format)
		return (0);
	va_start(args, format);
	i = -1;
	counter = 0;
	while (format[++i])
	{
		if (format[i] == '%')
		{
			ft_check_format(args, format[i + 1], &counter);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			counter++;
		}
	}
	va_end(args);
	return (counter);
}
