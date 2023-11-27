/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:29:32 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/27 12:39:41 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_here_doc(t_list *lst)
{
	t_list		*temp;
	t_command	*token;
	int			i;

	temp = lst;
	while (temp)
		{
		token = (t_command *)temp->content;
			i = -1;
		token->here_doc = false;
		while (token->red && token->red[++i])
		{
			if (token->red[i][0] == '<' && token->red[i][1] == '<')
			{
				add_str_to_array(&token->here, &token->red[i][2]);
				token->here_doc = true;
			}
			else if (token->red[i][0] == '<')
				token->here_doc = false;
		}
		if (token->here && token->here_doc)
		{
			token->std.in = here_doc(token);
			if (token->std.in == -1)
				return (1);
		}
		else if (token->here)
		{
			if (close(here_doc(token)) == -1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	parsing(char *input)
{
	t_list	*head;
	char	**parse_input;
	int		i;

	head = NULL;
	if (pipe_sintax(input))
	{
		display_error(1, "Syntax Error", true);
		shell()->segment_lst = head;
		return ;
	}
	parse_input = split_trim((find_replace(input, "|", 1)), 1);
	i = 0;
	while (parse_input[i])
	{
		ft_lstadd_back(&head, get_tokens(parse_input[i]));
		i++;
	}
//PFV	
	print_lst(head);
	
	free_array(&parse_input);
	shell()->segment_lst = head;
	init_built_in_flags(shell()->segment_lst);
	if (!shell()->error)
	{
//PFV
/*
		if (get_here_doc(shell()->segment_lst))
		{
			shell()->error = true;
			return ;
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
int pipe_sintax(char *input)
{
	int i;

	if (!input || !(*input))
		return (0);
	i = 0;
	while (input[i] && is_space(input[i]))
		i++;
	if (input[i] == '|')
		return (1);
	i = ft_strlen(input) - 1;
	while (input[i] && is_space(input[i]))
		i--;
	if (input[i] == '|')
		return (1);
	if (check_pipe(input))
		return (1);
	return (0);
}

/**
 * Verifica se há um pipe (|) entre os argumentos fornecidos e se a sintaxe do pipe
 * está correta, sem problemas de quotes e sem dois operadores de pipe consecutivos.
 *
 * @param input A string de entrada contendo os argumentos.
 * @return Retorna 1 se houver um pipe entre os argumentos, 
 *         caso contrário, retorna 0.
 */
int check_pipe(char *input)
{
	int i;
	char quote;
	char last_char;

	i = 0;
	last_char = 0;
	while (input[i])
	{
		if (is_quote(input[i]))
		{
			quote = input[i++];
			while (input[i] && input[i] != quote)
				i++;
			if (input[i++] != quote)
				return (0);
			last_char = 0;
		}
		else if (is_space(input[i]))
			i++;
		else if (last_char == '|' && input[i] == '|')
			return (1);
		else
			last_char = input[i++];
	}
	return (0);
}
