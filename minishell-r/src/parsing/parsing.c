/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:31:56 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/11/29 16:07:37 by pveiga-c         ###   ########.fr       */
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

/**
 * Função responsável por realizar o parsing da entrada.
 * 
 * @param input A entrada a ser analisada.
 */
// void parsing(char *line_prompt)
// {
// 	t_list *head;
// 	char **parse;
// 	char *temp_prompt;
// 	int i;

// 	head = NULL;
// 	temp_prompt = NULL;
// 	// Verifica se há erro de sintaxe de pipe
// 	if (pipe_sintax(line_prompt))
// 	{
// 		display_error(1, "Erro de sintaxe", true);
// 		shell()->segment_lst = head;
// 		return;
// 	}
// 	// Divide e remove espaços em branco da entrada
// 	temp_prompt = replace_quote(line_prompt, '|', 1);
// 	parse = split_trim(temp_prompt, 1);
// 	print_matriz(parse);
// 	i = 0;
// 	// Cria uma lista de tokens para cada parte da entrada
// 	while (parse[i])
// 	{
// 		ft_lstadd_back(&head, get_tokens(parse[i]));
// 		i++;
// 	}
// 	// Imprime a lista de tokens (apenas para fins de depuração)
// 	print_lst(head);

// 	free_array(&parse);
// 	shell()->segment_lst = head;
// 	init_built_in_flags(shell()->segment_lst);

// 	if (!shell()->error)
// 	{
// 		// Verifica se há here documents
// 		/*
// 		if (get_here_doc(shell()->segment_lst))
// 		{
// 			shell()->error = true;
// 			return;
// 		}
// 		get_reds(shell()->segment_lst);
// 		*/
// 	}
// }
void	print_matriz(char **matriz)
{
	int i;
	size_t j;

	i = 0;
	printf("---------------matriz-------------\n\n");
	while(i < 2)
	{
		j = 0;
		while(j < ft_strlen(matriz[i]))
		{
			printf("%c", matriz[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

/**
 * Verifica se a sintaxe de pipe está presente na string de entrada.
 * 
 * @param input A string de entrada a ser verificada.
 * @return Retorna 1 se a sintaxe estiver presente, caso contrário retorna 0.
 */
// int pipe_sintax(char *prompt)
// {
// 	int i;

// 	if (!prompt || !(*prompt))
// 		return (0);
// 	i = 0;
// 	while (prompt[i] && is_space(prompt[i]))
// 		i++;
// 	if (prompt[i] == '|')
// 		return (1);
// 	i = ft_strlen(prompt) - 1;
// 	while (prompt[i] && is_space(prompt[i]))
// 		i--;
// 	if (prompt[i] == '|')
// 		return (1);
// 	if (check_pipe(prompt))
// 		return (1);
// 	return (0);
// }

/**
 * Verifica se há um pipe (|) entre os argumentos fornecidos e se a sintaxe do pipe
 * está correta, sem problemas de quotes e sem dois operadores de pipe consecutivos.
 *
 * @param input A string de entrada contendo os argumentos.
 * @return Retorna 1 se houver um pipe entre os argumentos, 
 *         caso contrário, retorna 0.
 */
// int check_pipe(char *input)
// {
// 	int i;
// 	char quote;
// 	char last_char;

// 	i = 0;
// 	last_char = 0;
// 	while (input[i])
// 	{
// 		if (is_quote(input[i]))
// 		{
// 			quote = input[i++];
// 			while (input[i] && input[i] != quote)
// 				i++;
// 			if (input[i++] != quote)
// 				return (0);
// 			last_char = 0;
// 		}
// 		else if (is_space(input[i]))
// 			i++;
// 		else if (last_char == '|' && input[i] == '|')
// 			return (1);
// 		else
// 			last_char = input[i++];
// 	}
// 	return (0);
// }
