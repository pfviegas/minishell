/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 11:12:51 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/22 12:17:42 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Checks if a given string contains a separator character.
 * 
 * This function checks if the first character of the string is a separator character.
 * If the separator is a double redirection (<< or >>), it sets arr[0] to 2.
 * If the separator is a single redirection (< or >) or a pipe (|), it sets arr[0] to 1.
 * If the string does not contain a separator character, it sets arr[0] to 0.
 * 
 * @param str The string to be checked.
 * @param arr An integer array to store the result.
 * @return The value of arr[0], indicating the type of separator found (0, 1, or 2).
 */
int check_separator(char *str, int *arr)
{
	arr[0] = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		arr[0] = 2;
	else if (str[0] == '<' || str[0] == '>')
		arr[0] = 1;
	else if (str[0] == '|')
		arr[0] = 1;
	return (arr[0]);
}

/* faz o parsing do minishell 
Se separator encontrado e se encontrado novamente desligado
		if (separator != *str) -> inicializa separator -> separator = 1
		if (separator == *str) -> reinicia separator -> separator = 0;
Se separator = 0 e ' ' torna em 2 na str
Se for um token {<, <<, >, >>, |} e separator = 0: 
		  meter um 3 na casa do separador (tem de ser o unico 3 até ver uma 
		  algo diferente de token -> len = 0).
		  -Se nao for um pipe e len>0 --> manter o elemento na str
		  -Se nao for um pipe e arr==2 --> manter o proximo, fazendo dois
		  -No final meter um 2 extra e len passa para 1
Incrementamos o str aqui para poupar linhas
Caso geral: é ir colando as letras na string output e dizer que 
		  pode começar um novo token -> len = 0
*/

/**
 * @brief Parses the input string and modifies it according to the 
 * specified separator and array.
 * 
 * Parses the input string and modifies it based on the separator and array values.
 * It replaces single quotes and double quotes with the specified separator 
 * if it is not already set.
 * It replaces spaces with the value 2 if the separator is not set.
 * It checks for specific separators in the input string and modifies 
 * the output accordingly.
 * It also updates the array values based on the input string.
 * 
 * @param output The output string where the modified input will be stored.
 * @param input The input string to be parsed and modified.
 * @param separator The separator character to be used for replacing quotes.
 * @param arr The array to be updated based on the input string.
 */
void	parsing(char *output, char *input, char separator, int *arr)
{
	int		len;

	len = 0;
	while (input && *input)
	{
		if ((*input == '\'' || *input == '\"') && (!separator || separator == *input))
		{
			if (separator != *input) 
			{
				separator = (*input);
			}
		}
		else if (*input == ' ' && !separator)
			*input = 2;
		if (!separator && check_separator(input, arr))
		{
			*output++ = 2;
			*output++ = (3 - ((*input != '|') || (len != 0) || (arr[1] == 0)));
			if ((*input != '|' || !arr[1]) || len)
				*output++ = *input;
			if (input++ && *input != '|' && arr[0] == 2)
				*output++ = *input++;
			*output++ = 2;
			len++;
		}
		else if ((*input == 2 && arr[1]) || \
			((*input != 2 || *input++ != 2) && ++arr[1]))
			len = !(!!(*output++ = *input++));
	}
}
