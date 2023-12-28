/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:40:41 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/28 17:31:37 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função responsável por analisar e extrair uma palavra de uma 
 * determinada sequência de caracteres.
 *
 * @param seg A sequência de caracteres a ser analisada.
 * @param i O índice atual da sequência de caracteres.
 * @return A palavra extraída da sequência de caracteres.
 */

char	*parse_word(char *seg, int *i)
{
	char	*str;
	char	quote;
	int		flag;

	str = NULL;
	flag = 0;
	while (seg[*i] && !end_word(seg[*i], flag != 0))
	{
		if ((seg[*i] == '"' || seg[*i] == '\'') && flag == 0)
		{
			quote = seg[*i];
			flag = 1;
		}
		else if ((seg[*i] == '"' || seg[*i] == '\'') && quote == seg[(*i)])
			flag = 0;
		else if ((flag == 0 || (flag == 1 && quote == '"')) && seg[*i] == '$')
			expand_var(seg, &str, i);
		else
			add_char_string(&str, seg[*i]);
		(*i)++;
	}
	if (seg[*i] == '\0' && flag == 1)
		display_error(1, "Syntax error: doesn't handle unclosed quotes", true);
	return (str);
}

/**
 * Função responsável por expandir uma variável em uma string.
 * 
 * @param old A string original contendo a variável a ser expandida.
 * @param new O endereço da string expandida.
 * @param i O endereço do índice atual na string original.
 */
void	expand_var(char *old, char **new, int *i)
{
	int	start;

	(*i)++;
	if (old[(*i)] == '#')
		display_error(127, "0: command not found", true);
	if (ft_isdigit(old[(*i)]) || old[(*i)] == '@')
	{
		write(STDERR_FILENO, "", 0);
		shell()->error = true;
		shell()->exit_code = 0;
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
 * Função responsável por adicionar um caractere a uma string.
 * 
 * @param str O endereço da string à qual o caractere será adicionado.
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

/**
 * Verifica a posição do redirecionamento em uma string.
 *
 * Esta função verifica a posição do redirecionamento em uma string,
 * considerando o caractere atual e o próximo caractere. Ela retorna
 * o número de caracteres a serem pulados para encontrar o próximo
 * redirecionamento.
 *
 * @param seg A string a ser verificada.
 * @param curr_pos O ponteiro para a posição atual na string.
 * @return O número de caracteres a serem pulados para encontrar o próximo redirecionamento.
 */
int	check_red_pos(char *seg, int *curr_pos)
{
	int		i;
	char	quote;
	int		flag;

	i = 1;
	flag = 0;
	quote = 0;
	if (seg[*curr_pos] == seg[*curr_pos + 1])
		i++;
	while (seg[*curr_pos + i] == ' ' || seg[*curr_pos + i] == '\t')
		i++;
	while (seg[*curr_pos + i] && (seg[*curr_pos + i] != '<' && seg[*curr_pos + i] != '>'))
	{
		if(flag == 0 && (seg[*curr_pos + i] == '"' || seg[*curr_pos + i] == '\''))
		{
			quote = seg[*curr_pos + i];
			flag = 1;
		}
		else if(flag == 1 && (seg[*curr_pos + i] == quote))
			return (i + 1);
		if (flag == 0 && (seg[*curr_pos + i] == ' ' || seg[*curr_pos + i] == '\t'))
			return (i);
		i++;
	}
	return (i);
}

/**
 * Função responsável por fazer o parsing de um redirecionamento 
 * em uma string.
 *
 * @param seg A string contendo o segmento a ser analisado.
 * @param curr_pos A posição atual na string.
 * @return Um ponteiro para a string que representa o redirecionamento, 
 * ou NULL em caso de erro.
 */

char	*parse_redirection(char *seg, int *curr_pos)
{
	char	*temp;
	int		i;
	int		j;
	int		k;
	char	quote;
	int		flag;

	j = 0;
	k = -1;
	quote = 0;
	flag = 0;
	i = check_red_pos(seg, curr_pos);
//	if (i == 0)
//		return (NULL);
	temp = malloc(sizeof(char) * (i + 1));
	if (!temp)
		return (NULL);
	while (++k < i)
	{
		if(flag == 0 && (seg[*curr_pos + k] == '"' || seg[*curr_pos + k] == '\''))
		{
			quote = seg[*curr_pos + k];
			flag = 1;
			continue ;
		}
		if(flag == 1 && quote == seg[*curr_pos + k])
			flag = 0;
		if (flag == 0 && (seg[*curr_pos + k] == ' ' || seg[*curr_pos + k] == '\t' || seg[*curr_pos + k] == quote))
			continue ;
		else
			temp[j++] = seg[*curr_pos + k];
	}
	temp[j] = '\0';
	(*curr_pos) += i;
	printf("temp: %s\n", temp);
	return (temp);
}
