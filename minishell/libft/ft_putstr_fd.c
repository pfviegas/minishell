/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:38:57 by pviegas           #+#    #+#             */
/*   Updated: 2023/07/11 16:21:32 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Escreve uma string em um descritor de arquivo.
 *
 * A função ft_putstr_fd escreve a string 's' no descritor de arquivo 'fd'.
 *
 * @param s A string a ser escrita.
 * @param fd O descritor de arquivo onde a string será escrita.
 */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}
