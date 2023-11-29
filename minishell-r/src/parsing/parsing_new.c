/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:39:57 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/11/29 18:22:31 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void parsing(char *line_prompt)
{
	t_list *head;
	char **parse;
	char *temp_prompt;
	int i;

	head = NULL;
	temp_prompt = NULL;
	if (pipe_sintax(line_prompt))
	{
		display_error(1, "Erro de sintaxe", true);
		shell()->segment_lst = head;
		return;
	}
	temp_prompt = replace_pipe(line_prompt, '|', 1);
	parse = ft_split(temp_prompt, 1);
	parse = trim_parse(parse);
	i = -1;
	while (parse[++i])
	{
		ft_lstadd_back(&head, get_tokens(parse[i]));
		//printf("%d = %s\n",i, parse[i]);
	}
	//print_lst(head);
	free_array(&parse);
	shell()->segment_lst = head;
	init_built_in_flags(shell()->segment_lst);

	if (!shell()->error)
	{
		// Verifica se há here documents
		/*
		if (get_here_doc(shell()->segment_lst))
		{
			shell()->error = true;
			return;
		}
		get_reds(shell()->segment_lst);
		*/
	}
}

/**
 * Verifica se a sintaxe de pipe está presente na string de entrada.
 * 
 * @param input A string de entrada a ser verificada.
 * @return Retorna 1 se a sintaxe estiver presente, caso contrário retorna 0.
 */
int pipe_sintax(char *prompt)
{
	int i;

	if (!prompt || !(*prompt))
		return (0);
	i = 0;
	while (prompt[i] && is_space(prompt[i]))
		i++;
	if (prompt[i] == '|')
		return (1);
	i = ft_strlen(prompt) - 1;
	while (prompt[i] && is_space(prompt[i]))
		i--;
	if (prompt[i] == '|')
		return (1);
	if (check_pipe(prompt))
		return (1);
	return (0);
}

/**
 * Verifica se há um pipe (|) entre os argumentos fornecidos e se a sintaxe do pipe
 * está correta, sem problemas de quotes e sem dois operadores de pipe consecutivos.
 *
 * @param prompt A string de entrada contendo os argumentos.
 * @return Retorna 1 se houver um pipe entre os argumentos, 
 *         caso contrário, retorna 0.
 */
int check_pipe(char *prompt)
{
	int i;
	char quote;
	char last_char;

	i = 0;
	last_char = 0;
	while (prompt[i])
	{
		if (is_quote(prompt[i]))
		{
			quote = prompt[i++];
			while (prompt[i] && prompt[i] != quote)
				i++;
			if (prompt[i++] != quote)
				return (0);
			last_char = 0;
		}
		else if (is_space(prompt[i]))
			i++;
		else if (last_char == '|' && prompt[i] == '|')
			return (1);
		else
			last_char = prompt[i++];
	}
	return (0);
}