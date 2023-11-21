/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 11:54:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/13 11:54:11 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts an uppercase character to lowercase.
 *
 * The ft_tolower() function converts an uppercase character to its lowercase
 * equivalent if it is a valid uppercase character. If the input character is
 * not an uppercase character, it is returned unchanged.
 *
 * @param c The character to convert.
 *
 * @return The lowercase equivalent of the input character if it is a valid
 * uppercase character. Otherwise, the input character is returned unchanged.
 */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
