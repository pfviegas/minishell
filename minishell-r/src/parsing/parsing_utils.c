/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:31:43 by pveiga-c          #+#    #+#             */
/*   Updated: 2024/01/02 12:40:07 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Substitui um caractere específico por outro em uma string.
 *
 * @param str A string na qual o caractere será substituído.
 * @param search_char O caractere a ser substituído.
 * @param replace_char O caractere de substituição.
 * @return A string modificada.
 */
char	*replace_pipe(char *str, char search_char, char replace_char)
{
	int		i;
	int		in_quote;
	char	quote;

	i = -1;
	in_quote = 0;
	quote = 0;
	while (str[++i])
	{
		if ((str[i] == '"' || str[i] == '\'') && in_quote == 0)
		{
			quote = str[i];
			in_quote = 1;
		}
		else if (in_quote == 1 && str[i] == quote)
			in_quote = 0;
		else if (in_quote == 0 && str[i] == search_char)
			str[i] = replace_char;
	}
	return (str);
}

/**
 * Função que remove espaços em branco e tabulações de 
 * cada elemento de uma matriz de strings.
 *
 * @param str A matriz de strings a ser modificada.
 * @return A matriz de strings modificada.
 */
char	**trim_parse(char **str)
{
	char	*temp;
	int		i;

	i = -1;
	while (str[++i])
	{
		temp = ft_strtrim(str[i], " \t");
		free(str[i]);
		str[i] = temp;
	}
	return (str);
}

/**
 * Função responsável por obter os tokens de um comando de entrada.
 *
 * @param input_command O comando de entrada a ser analisado.
 * @return Uma lista encadeada contendo os tokens do comando.
 */
t_list	*get_tokens(char *input_command)
{
	t_command	*new_seg;
	int			i;

	i = 0;
	new_seg = malloc(sizeof(t_command));
	if (!new_seg)
		return (NULL);
	new_seg->built_in = false;
	init_command(new_seg);
	while (input_command[i] && !shell()->error)
		get_tokens_2(input_command, &i, new_seg);
	return (ft_lstnew((t_command *)new_seg));
}

void	get_tokens_2(char *input_command, int *i, t_command *new_seg)
{
	char	*temp;

	temp = NULL;
	if (input_command[*i] == '\t' || input_command[*i] == ' ')
		(*i)++;
	else if (input_command[*i] == '<' || input_command[*i] == '>')
	{
		check_quote_red(input_command, i);
		temp = parse_redirection(input_command, i);
		if (temp)
		{
			add_str_to_array(&new_seg->red, temp);
			free(temp);
		}
	}
	else
		get_tokens_3(temp, input_command, i, new_seg);
}

void	get_tokens_3(char *temp, char *input_command, int *i, \
t_command *new_seg)
{
	temp = parse_word(input_command, i);
	if (temp == NULL)
	{
		temp = "";
		add_str_to_array(&new_seg->cmd, temp);
	}
	else if (temp)
	{
		add_str_to_array(&new_seg->cmd, temp);
		free(temp);
	}
}
