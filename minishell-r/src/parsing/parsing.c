/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:31:56 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/08 12:58:51 by pviegas          ###   ########.fr       */
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
	temp_prompt = NULL;
	if (pipe_sintax(line_prompt))
	{
		display_error(1, "Erro de sintaxe", true);
		shell()->segments_lst = head;
		return ;
	}
	temp_prompt = replace_pipe(line_prompt, '|', 1);
	parse = ft_split(temp_prompt, 1);
	parse = trim_parse(parse);
	i = -1;
	while (parse[++i])
		ft_lstadd_back(&head, get_tokens(parse[i]));
	//print_lst(head);
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

/**
 * Verifica se a sintaxe de pipe está presente na string de entrada.
 * 
 * @param input A string de entrada a ser verificada.
 * @return Retorna 1 se a sintaxe estiver presente, caso contrário retorna 0.
 */
int	pipe_sintax(char *prompt)
{
	int	i;

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
		if (check_quote(prompt[i]))
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

void	print_matriz(char **matriz)
{
	int		i;
	size_t	j;

	i = 0;
	printf("---------------matriz-------------\n\n");
	while (i < 2)
	{
		j = 0;
		while (j < ft_strlen (matriz[i]))
		{
			printf("%c", matriz[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}