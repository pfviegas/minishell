/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_ct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:12:16 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/28 13:38:39 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putptr_ct(void *ptr, size_t *counter)
{
	char			*str;
	unsigned long	ptr_address;

	if (ptr == NULL)
		ft_putstr_ct("(nil)", counter);
	else
	{
		ptr_address = (unsigned long)ptr;
		ft_putstr_ct("0x", counter);
		str = ft_base_conv(ptr_address, "0123456789abcdef");
		ft_putstr_ct(str, counter);
		free(str);
	}
}
