/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_new_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:42:03 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/01 15:31:11 by pveiga-c         ###   ########.fr       */
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
			if (temp)
			{
				add_str_to_array(&new_seg->red, temp);
				free(temp);
			}
		}
		else
		{
			temp = parse_word(input_command, &i);
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
	while(redirect && redirect[i] && !is_space(redirect[i]))
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
	(*curr_pos) += i;
	return (temp);
}

/**
 * Função responsável por analisar uma palavra em uma determinada 
 * posição de uma string.
 * 
 * @param seg      A string a ser analisada.
 * @param curr_pos A posição atual na string.
 * @return         Um ponteiro para a palavra analisada.
 */
char *parse_word(char *seg, int *i)
{
	char *str;
	char quote;
	//char start;

	str = NULL;
	quote = 0;
	//start = *i;
	while (seg[*i] && !end_word(seg[*i], quote != 0))
	{
		if (is_quote(seg[*i]) && quote == 0)
			quote = seg[*i];
		else if (is_quote(seg[*i]) && quote == seg[(*i)])
			quote = 0;
		else if ((quote == 0 || (quote != 0 && quote == '"')) && seg[*i] == '$')
			expand_var(seg, &str, i);
		else
			add_char_string(&str, seg[*i]);
		(*i)++;
	}
	if (seg[*i] == '\0' && quote != 0)
		display_error(1, "Syntax error: doesn't handle unclosed quotes", true);
	printf("input = %s\n", str);
	return (str);
}

/**
 * Expande uma variável em uma string.
 *
 * Expande uma variável em uma string, substituindo-a pelo seu valor.
 * A variável é identificada pelo caractere '$' seguido pelo nome da variável.
 * Se a variável for um número, ela não será expandida.
 * Se a variável for o caractere '?', ela será expandida para o código de 
 * saída do último comando executado.
 * Caso contrário, a função chama a função 'expander' para expandir a variável.
 * Se a variável não for encontrada, a função adiciona o caractere '$' à string.
 *
 * @param old_str A string original contendo a variável a ser expandida.
 * @param new_str O ponteiro para a string resultante da expansão.
 * @param curr_pos O ponteiro para a posição atual na string original.
 */
void expand_var(char *old, char **new, int *i)
{
	int start;

	(*i)++;
	if (ft_isdigit(old[(*i)]) || old[(*i)] == '@')
		return;
	if (old[(*i)] == '#')
	{
		printf("0");
		return;
	}
	start = (*i);
	while (old[(*i)] && !end_var(old[(*i)]))
		(*i)++;
	if (old[(*i)] == '?')
		expand_exit(new, i);
	else if (start != *i)
		expander(old, new, start, i);
	else
		add_char_string(new, '$');
	(*i)--;
}

/**
 * Adiciona um caractere a uma string.
 *
 * Esta função recebe um ponteiro para uma string e um caractere `c` e adiciona 
 * o caractere à string. 
 * Se a string for nula, a função cria uma nova string contendo apenas o char.
 * Caso contrário, a função aloca memória suficiente para acomodar o caractere 
 * adicional e copia a string original para a nova string, seguida do char `c`. 
  *
 * @param str O ponteiro para a string.
 * @param c O caractere a ser adicionado.
 */
void	add_char_string(char **str, char c)
{
	char	*new;
	int		i;


	if (!(*str))
	{
		new = malloc(2);
		if (!new)
			return ;
		new[0] = c;
		new[1] = '\0';
		*str = new;
		return ;
	}
	new = malloc(ft_strlen(*str) + 2);
	if (!new)
		return ;
	i = -1;
	while ((*str)[++i])
		new[i] = (*str)[i];
	new[i] = c;
	new[i + 1] = '\0';
	free(*str);
	*str = new;
}
