/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 15:35:31 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/21 17:01:17 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Displays a syntax error message and frees the input string.
 * 
 * Is called when a syntax error is encountered while parsing the input.
 * It displays an error message indicating the unexpected token 
 * and frees the input string.
 * The function also sets the status to 2 and prompts for a new command.
 * 
 * @param str The unexpected token causing the syntax error.
 * @param input The input string to be freed.
 * @param size The size of the input string.
 */
void syntax_error(char *str, char *input, int size)
{
	int i;

	i = -1;
	write(2, "minishell: syntax error near unexpected token `", 47);
	while (size != 0 && str[++i])
	{
		write(2, &str[i], 1);
		size--;
	}
	write(2, "\'\n", 2);
	if (input)
		free(input);
	g_data.exit_status = 2;
	prompt();
}

/**
 * @brief Handling the separators in the input string.
 * 
 * This function analyzes the input string and handles the separators, 
 * such as '|'. It checks for syntax errors related to the separators 
 * and counts the number of words.
 * 
 * @param input The input string to be analyzed.
 * @param i The current index in the input string.
 * @param size The size of the current word being analyzed.
 * @param words A pointer to the variable storing the number of words.
 */
void separator_handling(char *input, int i, int size, int *words)
{
	int temp;
	int word_count;
	int separator;

	temp = 0;
	word_count = 0;
	separator = 0;

	// Check if the separator is '|'
	if (input[i] == '|')
		separator = input[i];
	// Check for syntax errors related to '||' and '|'
	if (input[i] == '|' && input[i + 1] == '|')
		syntax_error("||", input, 2);
	else if (*words == 0 && input[i] == '|')
		syntax_error("|", input, 1);

	i += size;

	// Analyze the remaining characters in the input string
	while (input[i])
	{
		// Check for a separator syntax errors related to separators and count the number of words
		if (((!separator && check_redir_pipe(&input[i], &temp)) || 
			(separator && check_redir_pipe(&input[i], &temp) == 4)) && 
			!word_count)
			syntax_error(&input[i], input, temp);
		else if (input[i] != 32)
			word_count++;
		i++;
	}

	// Check for syntax error related to newline
	if (!word_count)
		syntax_error("newline", input, 8);
}

/**
 * Checks if a given string contains a redirection or pipe symbol 
 * and returns the corresponding value.
 * 
 * @param str The string to check.
 * @param arr An integer array to store the result.
 * @return The value indicating the type of symbol found:
 *         - 0: No redirection or pipe symbol found.
 *         - 1: Single redirection symbol found (< or >).
 *         - 2: Double redirection symbol found (<< or >>).
 *         - 4: Pipe symbol found (|).
 */
int check_redir_pipe(char *str, int *arr)
{
	arr[0] = 0;
	if ((str[0] == '<' && str[1] == '<') || (str[0] == '>' && str[1] == '>'))
		arr[0] = 2;
	else if (str[0] == '<' || str[0] == '>')
		arr[0] = 1;
	else if (str[0] == '|')
		arr[0] = 1;
	else if (str[0] == ';')
		arr[0] = 1;
	if (str[0] == '|')
		return (4);
	else
		return (arr[0]);
}

/**
 * @brief Handles the syntax of the input string.
 * 
 * Analyzes the input string character by character and performs
 * various operations based on the syntax rules. It keeps track of quotes, 
 * redirections, pipes, and counts the number of arguments.
 * 
 * @param input The input string to be processed.
 */
void	syntax_handling(char *input)
{
	int	arr[5];
	int	i;

	i = 0;
	while (i <= 4)
		arr[i++] = 0;
	if (!input)
		return ;
	while (input[arr[0]])
	{
		if ((input[arr[0]] == '\'' || input[arr[0]] == '\"') \
			&& (!arr[4] || arr[4] == input[arr[0]]))
			arr[4] = (input[arr[0]]) * (arr[4] != input[arr[0]]);
		if (!arr[4] && check_redir_pipe(&input[arr[0]], &(arr[1])))
			separator_handling(input, arr[0], arr[1], &(arr[2]));
		else if ((input[arr[0]] == '\"' && !arr[3]) || \
			(input[arr[0]] == '\'' && !arr[3]))
			quotes_handling(input, arr[0], &arr[3]);
		else if (input[arr[0]] == arr[3])
			arr[3] = 0;
		else if (input[arr[0]] != 32)
			(arr[2])++;
		(arr[0]) += (arr[1] == 2);
		(arr[0])++;
	}
}