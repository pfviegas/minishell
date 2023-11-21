/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexl_ct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:13:10 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/28 11:33:40 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthexl_ct(unsigned int num, size_t *counter)
{
	char	*str;

	str = ft_base_conv(num, "0123456789abcdef");
	ft_putstr_ct(str, counter);
	free(str);
}
