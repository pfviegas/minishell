/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:55:26 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/21 17:00:57 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Treats quotes in the input string.
 * 
 * This function takes an input string, a position index, and a flag pointer as parameters.
 * It sets the flag to the character at the given index and searches for the matching closing quote.
 * If the closing quote is found, the function returns. Otherwise, it calls the syntax_error function.
 * 
 * @param input The input string.
 * @param i The position index.
 * @param flag A pointer to the flag variable.
 */
void	quotes_handling(char *input, int i, int *flag)
{
	char	c;

	c = input[i];
	*flag = c;
	while (input[++i])
	{
		if (c == input[i])
			return ;
	}
	syntax_error(&c, input, 1);
}