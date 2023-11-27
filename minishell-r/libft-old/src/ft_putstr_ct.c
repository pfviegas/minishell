/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_ct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 14:21:05 by pviegas           #+#    #+#             */
/*   Updated: 2023/08/14 14:30:39 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

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
