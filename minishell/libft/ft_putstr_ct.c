/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_ct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:21:05 by pviegas           #+#    #+#             */
/*   Updated: 2023/05/01 15:33:57 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_ct(char *s, size_t *counter)
{
	if (s)
	{
		write(1, s, ft_strlen(s));
		(*counter) = (*counter) + ft_strlen(s);
	}
	else
		ft_putstr_ct("(null)", counter);
}
