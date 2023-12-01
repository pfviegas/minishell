/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:29:22 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/01 14:53:29 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
void expand_var(char *old_str, char **new_str, int *curr_pos)
{
	int start;

	(*curr_pos)++;
	if (ft_isdigit(old_str[(*curr_pos)]) || old_str[(*curr_pos)] == '@')
		return;
	if (old_str[(*curr_pos)] == '#')
	{
		printf("0");
		return;
	}
	start = (*curr_pos);
	while (old_str[(*curr_pos)] && !end_variable(old_str[(*curr_pos)]))
		(*curr_pos)++;
	if (old_str[(*curr_pos)] == '?')
		expand_exit_code(new_str, curr_pos);
	else if (start != *curr_pos)
		expander(old_str, new_str, start, curr_pos);
	else
		add_char_string(new_str, '$');
	(*curr_pos)--;
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
		display_error(1, "Minishell doesn't interpreted unclosed quotes or special characters", true);
	if (!str && was_q)
		str = ft_calloc(1, 1);
	return (str);
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
	char	*new_str;
	int		i;

	if (!(*str))
	{
		new_str = malloc(2);
		if (!new_str)
			return ;
		new_str[0] = c;
		new_str[1] = '\0';
		*str = new_str;
		return ;
	}
	i = 0;
	while ((*str)[i])
		i++;
	new_str = malloc(i + 2);
	if (!new_str)
		return ;
	i = -1;
	while ((*str)[++i])
		new_str[i] = (*str)[i];
	new_str[i] = c;
	new_str[i + 1] = '\0';
	free(*str);
	*str = new_str;
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
	char *final;

	redirect = NULL;
	temp = NULL;
	final = NULL;

	// Adiciona o caractere atual à string redirect
	add_char_string(&redirect, seg[(*curr_pos)++]);

	// Verifica se o caractere atual é igual ao próximo caractere
	if (seg[(*curr_pos) - 1] == seg[(*curr_pos)])
		add_char_string(&redirect, seg[(*curr_pos)++]);

	// Ignora os espaços em branco
	while (seg[(*curr_pos)] && is_space(seg[*curr_pos]))
		(*curr_pos)++;

	// Verifica se o caractere atual não é um recionamento
	if (seg[(*curr_pos)] && !is_great_less(seg[(*curr_pos)]))
	{
		// Faz o parsing da palavra seguinte
		temp = parse_word(seg, curr_pos, redirect);
		if (temp)
		{
			// Concatena a string redirect com a palavra parseada
			final = ft_strjoin(redirect, temp);
			free(temp);
		}
	}
	else
		display_error(1, "Syntax Error", true);
	free(redirect);
	return final;
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
			temp = parse_word(input_command, &i, NULL);
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
 * Função que divide uma string em um array de strings, 
 * utilizando um caractere delimitador e remove os espaços em branco 
 * e tabulações de cada elemento do array.
 *
 * @param str A string a ser dividida e trimada.
 * @param c   O caractere delimitador utilizado para dividir a string.
 * @return    Um array de strings contendo os elementos divididos e trimados.
 */
char **split_trim(char *str, char c)
{
	char **array;
	char *temp;
	int i;

	array = ft_split(str, c);
	if (!array)
		return NULL;
	i = -1;
	while (array[++i])
	{
		temp = ft_strtrim(array[i], " \t");
		free(array[i]);
		array[i] = temp;
	}
	return array;
}


/**
 * Substitui caracteres em uma string.
 *
 * Esta função substitui os caracteres especificados em `search_set` 
 * por `replace_char` na string `str`. A substituição ocorre apenas 
 * fora de aspas, ignorando os caracteres dentro de aspas. 
 * A função retorna a string modificada.
 *
 * @param str            A string a ser modificada.
 * @param search_set     Os caracteres a serem substituídos.
 * @param replace_char   O caractere de substituição.
 * @return               A string modificada.
 */
char	*find_replace(char *str, char *search_set, char replace_char)
{
	int		i;
	int		in_quote;
	char	quote;

	i = -1;
	in_quote = 0;
	quote = 0;
	while (str[++i])
	{
		if (is_quote(str[i]) && !in_quote)
		{
			quote = str[i];
			in_quote = !in_quote;
		}
		else if (in_quote && str[i] == quote)
			in_quote = !in_quote;
		else if (!in_quote && is_in_set(str[i], search_set))
			str[i] = replace_char;
	}
	return (str);
}

/**
 * Função responsável por obter as redirecionamentos de entrada e saída 
 * de uma lista de comandos.
 *
 * @param lst A lista de comandos.
 */
void	get_redirects(t_list *lst)
{
	t_list		*temp;
	t_command	*seg;
	int			i;
	char		*msg;

//PFV
//	print_lst(lst);

	temp = lst;
	while (temp)
	{
		seg = (t_command *)temp->content;
		i = -1;
		while (seg->red && seg->red[++i])
		{
			if (seg->red[i][0] == '<' && seg->red[i][1] != '<')
			{
				if (seg->std.in != -1 && !seg->here_doc)
					close(seg->std.in);
				if (access(&seg->red[i][1], F_OK))
				{
					seg->redirect_error = 1;
					break ;
				}
				if (!seg->here_doc)
				{
					seg->std.in = open(&seg->red[i][1], O_RDONLY);
					if (seg->std.in == -1)
					{
						seg->redirect_error = 1;
						break ;
					}
				}
			}
			else
			{
				if (seg->std.out != -1)
					close(seg->std.out);
				if (seg->red[i][0] == '>' && seg->red[i][1] == '>')
				{
					seg->std.out = open(&seg->red[i][2], O_RDWR | O_CREAT | O_APPEND, 0644);
					if (seg->std.out == -1)
					{
						seg->redirect_error = 1;
						break ;
					}
				}
				else if (seg->red[i][0] == '>' && seg->red[i][1] != '>')
				{
					seg->std.out = open(&seg->red[i][1], O_RDWR | O_CREAT | O_TRUNC, 0644);
					if (seg->std.out == -1)
					{
						seg->redirect_error = 1;
						break ;
					}
				}
			}
		}
		if (seg->redirect_error == 1)
		{
//PFV
//			display_error(1, strerror(errno), false);
			msg = ft_strjoin("minishell: ", strerror(errno));
			display_error(1, msg, false);
			free(msg);
		}
		temp = temp->next;
	}
}
