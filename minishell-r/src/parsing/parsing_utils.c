/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 17:31:43 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/07 16:43:34 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Substitui um caractere de busca por um caractere de 
 * substituição em uma string.
 *
 * @param str A string na qual a substituição será feita.
 * @param search_char O caractere a ser substituído.
 * @param replace_char O caractere de substituição.
 * @return A string modificada após a substituição.
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
		if (check_quote(str[i]) && in_quote == 0)
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
 * Função que divide uma string em um array de strings, 
 * utilizando um caractere delimitador e remove os espaços em branco 
 * e tabulações de cada elemento do array.
 *
 * @param str A string a ser dividida e trimada.
 * @param c   O caractere delimitador utilizado para dividir a string.
 * @return    Um array de strings contendo os elementos divididos e trimados.
 */

char	**trim_parse(char **str)
{
	char	*temp;
	int		i;

	i = -1;
	while (str[++i])
	{
		temp = ft_strtrim(str[i], " \t");
		str[i] = temp;
	}
	free(str[i]);
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

	if (is_space(input_command[*i]))
		(*i)++;
	else if (is_great_less(input_command[*i]))
	{
		temp = parse_redirection(input_command, i);
		if (temp)
		{
			add_str_to_array(&new_seg->red, temp);
			free(temp);
		}
	}
	else
	{
		temp = parse_word(input_command, i);
		if (temp)
		{
			add_str_to_array(&new_seg->cmd, temp);
			free(temp);
		}
	}
}

/**
 * Função responsável por analisar e fazer o parsing de uma redirecionamento.
 *
 * @param seg      Ponteiro para a string contendo o segmento a ser analisado.
 * @param curr_pos Ponteiro para a posição atual na string.
 * @return         Ponteiro para a string resultante do parsing.
 */

char	*parse_redirection(char *seg, int *curr_pos)
{
	char	*redirect;
	char	*temp;
	int		i;
	int		j;

	temp = NULL;
	i = 1;
	j = 1;
	redirect = &seg[(*curr_pos)];
	while (redirect && is_space(redirect[i]))
		i++;
	if (is_great_less(redirect[i]))
	{
		display_error(1, "Syntax Error", true);
		return (NULL);
	}
	i = 0;
	temp = malloc(sizeof(char *) * ft_strlen(redirect));
	while (redirect && redirect[i] && !is_space(redirect[i]))
	{
		parse_redirection_2(temp, redirect, &i, &j);
	}
	(*curr_pos) += i;
	return (temp);
}
