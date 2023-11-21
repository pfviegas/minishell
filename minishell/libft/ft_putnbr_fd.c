/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:42:27 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/11 16:20:02 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Escreve um número inteiro em um descritor de arquivo.
 *
 * A função ft_putnbr_fd escreve o número inteiro 'n' no descritor de 
 * arquivo 'fd'.
 *
 * @param n O número inteiro a ser escrito.
 * @param fd O descritor de arquivo onde o número será escrito.
 */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	long	nb;

	nb = (long)n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
	{
		ft_putnbr_fd(nb / 10, fd);
	}
	c = (char)(nb % 10 + '0');
	write(fd, &c, 1);
}
