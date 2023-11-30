/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_new_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:42:03 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/11/30 18:48:10 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Substitui um caractere de busca por um caractere de substituição em uma string.
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
		if (is_quote(str[i]) && in_quote == 0)
		{
			quote = str[i];
			in_quote = 1;
		}
		else if (in_quote == 1 && str[i] == quote)
			in_quote = 0;
		else if (in_quote == 0 && str[i] == search_char) // is_in_set(str[i], search_char)
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
char **trim_parse(char **str)
{
	char *temp;
	int i;

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
	char	*temp;
	t_command	*new_seg;
	int		i;

	i = 0;
	
	new_seg = malloc(sizeof(t_command));
	if (!new_seg)
		return (NULL);
	new_seg->built_in = false;
//  Inicializa a estrutura t_command com valores padrão.
	init_command(new_seg);
	//printf("%s\n\n\n",input_command);
	while (input_command[i] && !shell()->error)
	{
		if (is_space(input_command[i]))
			i++;
		else if (is_great_less(input_command[i]))
		{
			temp = parse_redirection(input_command, &i);
			printf("final1 = %s\n", temp);
			
			if (temp)
			{
				add_str_to_array(&new_seg->red, temp);
				free(temp);
			}
		}
		else
		{
			temp = parse_word(input_command, &i, NULL);
	printf("final2 = %s\n", temp);
			
			if (temp)
			{
				add_str_to_array(&new_seg->cmd, temp);
				free(temp);
			}
		}
	}
	return (ft_lstnew((t_command *)new_seg));
}

/**
 * Função responsável por analisar e fazer o parsing de uma redirecionamento.
 *
 * @param seg      Ponteiro para a string contendo o segmento a ser analisado.
 * @param curr_pos Ponteiro para a posição atual na string.
 * @return         Ponteiro para a string resultante do parsing.
 */
char *parse_redirection(char *seg, int *curr_pos)
{
	char *redirect;
	char *temp;
	int i;
	int j;

//PCC
	temp = NULL;
	i = 1;
	j = 1;
	redirect = &seg[(*curr_pos)];
	while (redirect && is_space(redirect[i]))
			i++;
	if(is_great_less(redirect[i]))
	{
		display_error(1, "Syntax Error", true);
		return(NULL);
	}
	i = 0;
	temp = malloc(sizeof(char *) * ft_strlen(redirect));
	while(redirect && redirect[i])
	{
		temp[i] = redirect[i];
		if(redirect[i] == redirect[i + 1])
		{
			temp[i + 1] = redirect[i + 1];
			i++;
			j++;
		}
		i++;
		while (redirect && is_space(redirect[i]))
			i++;
		if(redirect && !is_great_less(redirect[i]))
		{
			while(redirect && redirect[i] && !is_space(redirect[i]))
				temp[j++] = redirect[i++];
		}
	}
	(*curr_pos) += j;
	printf("final = %s\n", temp);
	return (temp);
}

/**
 * Função responsável por analisar uma palavra em uma determinada 
 * posição de uma string.
 * 
 * @param seg      A string a ser analisada.
 * @param curr_pos A posição atual na string.
 * @param red      A string de redirecionamento.
 * @return         Um ponteiro para a palavra analisada.
 */
char *parse_word(char *seg, int *curr_pos, char *red)
{
	char *str;
	char quote;
	char was_q;
	char start;

	str = NULL;
	was_q = false;
	quote = 0;
	start = *curr_pos;
	while (seg[*curr_pos] && !end_word(seg[*curr_pos], quote))
	{
		if (is_quote(seg[*curr_pos]) && !quote)
		{
			quote = seg[*curr_pos];
			was_q = true;
		}
		else if (is_quote(seg[*curr_pos]) && quote == seg[(*curr_pos)])
			quote = 0;
		else if ((!quote || (quote && quote == '"')) && seg[*curr_pos] == '$' && ft_strcmp(red, "<<") != 0)
			expand_var(seg, &str, curr_pos);
		else
			add_char_string(&str, seg[*curr_pos]);
		(*curr_pos)++;
	}
	if (seg[*curr_pos] == '\0' && quote)
		display_error(1, "Minishell doesn't handle quotation marks", true);
	if (!str && was_q)
		str = ft_calloc(1, 1);
	return (str);
}
