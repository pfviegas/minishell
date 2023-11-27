/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_ct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 11:04:12 by pviegas           #+#    #+#             */
/*   Updated: 2023/08/14 14:30:39 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	ft_putuint_ct(unsigned int num, size_t *counter)
{
	char	*str;

	str = ft_base_conv(num, "0123456789");
	ft_putstr_ct(str, counter);
	free(str);
}
