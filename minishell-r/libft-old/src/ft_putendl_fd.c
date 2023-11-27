/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 13:39:17 by pviegas           #+#    #+#             */
/*   Updated: 2023/08/14 14:30:39 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Escreve uma string seguida de uma quebra de linha em um descritor 
 * de arquivo.
 *
 * A função ft_putendl_fd escreve a string 's' seguida de uma quebra de linha 
 * no descritor de arquivo 'fd'.
 *
 * @param s A string a ser escrita.
 * @param fd O descritor de arquivo onde a string será escrita.
 */

#include "../include/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
		write(fd, "\n", 1);
	}
}
