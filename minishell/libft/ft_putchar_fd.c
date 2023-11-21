/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:38:28 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/03 12:13:42 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Escreve um caractere em um descritor de arquivo.
 *
 * A função ft_putchar_fd escreve o caractere 'c' no descritor de arquivo 'fd'.
 *
 * @param c O caractere a ser escrito.
 * @param fd O descritor de arquivo onde o caractere será escrito.
 */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
