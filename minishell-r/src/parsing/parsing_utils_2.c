/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:40:41 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/08 17:45:36 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Função responsável por realizar a análise e manipulação de redirecionamentos.
 * 
 * @param temp     O array de caracteres temporário para armazenar o resultado.
 * @param redirect O array de caracteres contendo a string de redirecionamento.
 * @param i        O ponteiro para a posição atual no array redirect.
 * @param j        O ponteiro para a posição atual no array temp.
 */
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
	{
		printf("0: comando não encontrado\n");
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
	//print_lst(lst);

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
			msg = ft_strjoin("minishell: ", strerror(errno));
			display_error(1, msg, false);
			free(msg);
		}
		temp = temp->next;
	}
}
