/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 16:55:26 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/22 16:53:17 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Deletes quotes from a given string.
 * 
 * This function removes single quotes ('), double quotes (") or both from a given string.
 * The modified string is stored in a new dynamically allocated memory block.
 * 
 * @param input The address of the string to be modified.
 * @param c The type of quotes to be deleted. If c is 0, both single and double quotes are deleted.
 * 
 * @note The original string is freed and replaced with the modified string.
 */
void	delete_quotes_str(char **input, char c)
{
	char	*temp;
	int		i;
	int		j;
	int		flag;

	i = -1;
	j = 0;
	flag = 0;
	temp = ft_calloc(ft_strlen(*input) + 1, 1);
	if (!temp)
		return ;
	while (input[0][++i])
	{
		if ((input[0][i] == '\'' || input[0][i] == '\"') \
			&& (!c || c == input[0][i]) && (!flag || flag == input[0][i]))
			c = input[0][i] * (c != input[0][i]);
		else
			temp[j++] = input[0][i];
		if (c)
			flag = c;
		else
			flag = 0;
	}
	free(*input);
	*input = temp;
}

/**
 * @brief Deletes quotes from each string in the input array.
 * 
 * Iterates through each string in the input array and checks if it contains
 * single quotes ('') or double quotes (""). If quotes are found, the function calls
 * delete_quotes_str() to remove the quotes from the string.
 * 
 * @param input The array of strings to process.
 */
void delete_quotes(char **input)
{
	int k;

	k = -1;
	while (input[++k])
	{
		if (ft_strchr(input[k], '\'') || ft_strchr(input[k], '\"'))
			delete_quotes_str(&input[k], 0);
	}
}

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