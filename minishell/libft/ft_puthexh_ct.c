/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexh_ct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:13:15 by pviegas           #+#    #+#             */
/*   Updated: 2023/04/28 11:33:59 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthexh_ct(unsigned int num, size_t *counter)
{
	char	*str;

	str = ft_base_conv(num, "0123456789ABCDEF");
	ft_putstr_ct(str, counter);
	free(str);
}
