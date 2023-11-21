/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:53:41 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 11:53:41 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts a lowercase character to uppercase.
 *
 * The ft_toupper() function converts a lowercase character to its uppercase
 * equivalent if it is a valid lowercase character. If the input character is
 * not a lowercase character, it is returned unchanged.
 *
 * @param c The character to convert.
 *
 * @return The uppercase equivalent of the input character if it is a valid
 * lowercase character. Otherwise, the input character is returned unchanged.
 */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
