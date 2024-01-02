/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:31:56 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/02 12:40:23 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parsing(char *line_prompt)
{
	t_list	*head;
	char	**parse;
	char	*temp_prompt;
	int		i;

	head = NULL;
	parsing_2(line_prompt, head);
	temp_prompt = replace_pipe(line_prompt, '|', 1);
	parse = ft_split(temp_prompt, 1);
	parse = trim_parse(parse);
	i = -1;
	while (parse[++i])
		ft_lstadd_back(&head, get_tokens(parse[i]));
	free_array(&parse);
	shell()->segments_lst = head;
	init_built_in_flags(shell()->segments_lst);
	if (!shell()->error)
	{
		if (get_here_doc(shell()->segments_lst))
		{
			shell()->error = true;
			return ;
		}
		get_redirects(shell()->segments_lst);
	}
}

void	parsing_2(char *line_prompt, t_list *head)
{
	if (pipex(line_prompt))
	{
		display_error(2, "minishell: syntax error near unexpected token `||'", \
			true);
		shell()->segments_lst = head;
		return ;
	}
}

/**
 * Verifica se a sintaxe de pipe está presente na string de entrada.
 * 
 * @param input A string de entrada a ser verificada.
 * @return Retorna 1 se a sintaxe estiver presente, caso contrário retorna 0.
 */
int	pipex(char *prompt)
{
	int	i;

	if (!prompt || !(*prompt))
		return (0);
	i = 0;
	while (prompt[i] && (prompt[i] == '\t' || prompt[i] == ' '))
		i++;
	if (prompt[i] == '|')
		return (1);
	i = ft_strlen(prompt) - 1;
	while (prompt[i] && (prompt[i] == '\t' || prompt[i] == ' '))
		i--;
	if (prompt[i] == '|')
		return (1);
	if (check_pipe(prompt))
		return (1);
	return (0);
}

/**
 * Verifica se há um caractere de pipe '|' na string de prompt.
 *
 * @param prompt A string de prompt a ser verificada.
 * @return Retorna 1 se houver um caractere de pipe '|' na string 
 * de prompt, caso contrário retorna 0.
 */
int	check_pipe(char *prompt)
{
	int		i;
	char	quote;
	char	last_char;

	i = 0;
	last_char = 0;
	while (prompt[i])
	{
		if (prompt[i] == '"' || prompt[i] == '\'')
		{
			quote = prompt[i++];
			while (prompt[i] && prompt[i] != quote)
				i++;
			if (prompt[i++] != quote)
				return (0);
			last_char = 0;
		}
		else if (prompt[i] == '\t' || prompt[i] == ' ')
			i++;
		else if (last_char == '|' && prompt[i] == '|')
			return (1);
		else
			last_char = prompt[i++];
	}
	return (0);
}

void	check_quote_red(char *input_command, int *i)
{
	int	j;

	j = 1;
	shell()->flag_quote = 0;
	if (input_command[*i + j] == '<' || input_command[*i + j] == '>')
		j++;
	while (input_command[*i + j] == ' ')
		j++;
	if (input_command[*i + j] == '"' || input_command[*i + j] == '\'')
	{
		shell()->flag_quote++;
		j++;
	}
	while (input_command[*i + j] && (input_command[*i + j] != '"' \
	|| input_command[*i + j] != '\''))
		j++;
	j--;
	if (input_command[*i + j] == '"' || input_command[*i + j] == '\'')
	{
		shell()->flag_quote++;
		j++;
	}
}
