/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:40:41 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/07 16:58:49 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	parse_redirection_2(char *temp, char *redirect, int *i, int *j)
{
	temp[*i] = redirect[*i];
	if (redirect[*i] == redirect[*i + 1])
	{
		temp[*i + 1] = redirect[*i + 1];
		(*i)++;
		(*j)++;
	}
	(*i)++;
	while (redirect && is_space(redirect[*i]))
		(*i)++;
	if (redirect && !is_great_less(redirect[*i]))
	{
		while (redirect && redirect[*i] && !is_space(redirect[*i]))
			temp[(*j)++] = redirect[(*i)++];
	}
}

/**
 * Função responsável p						
or analisar uma palavra em uma determinada 
 * posição de uma string.
 * 
 * @param seg      A string a ser analisada.
 * @param curr_pos A posição atual na string.
 * @return         Um ponteiro para a palavra analisada.
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
		if (check_quote(seg[*i]) && flag == 0)
		{
			quote = seg[*i];
			flag = 1;
		}						

		else if (check_quote(seg[*i]) && quote == seg[(*i)])
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
 * Expande uma variável em uma string.
 *
 * Expande uma variável em uma string, substituindo-a pelo seu valor.
 * A variável é ident	//char start;
env or encontrada, a função adiciona o caractere '$' à string.
 *
 * @param old_str A str						
ing original contendo a variável a ser expandida.
 * @param new_str O ponteiro para a string resultante da expansão.
 * @param curr_pos O ponteiro para a posição atual na string original.
 */
void	expand_var(char *old, char **new, int *i)
{
	int	start;

	(*i)++;
	if (old[(*i)] == '#')
	{
		printf("0: command not found\n");
		return ;
	}
	if (ft_isdigit(old[(*i)]) || old[(*i)] == '@')
		return ;
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
