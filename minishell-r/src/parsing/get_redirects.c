/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:40:41 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/28 15:55:12 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

	temp = lst;
	while (temp)
	{
		seg = (t_command *)temp->content;
		i = -1;
		while (seg->red && seg->red[++i])
		{
			if (seg->red[i][0] == '<' && seg->red[i][1] != '<')
				get_redirects_2(seg, &i);
			else
				get_redirects_3(seg, &i);
		}
		temp = temp->next;
	}
}

/**
 * Função responsável por lidar com redirecionamentos de entrada.
 * Fecha o descritor de arquivo de entrada atual, se existir, 
 * e verifica se o arquivo de redirecionamento existe. 
 * Em seguida, abre o arquivo de redirecionamento no modo 
 * de leitura e atualiza o descritor de arquivo de entrada.
 * 
 * @param seg Ponteiro para a estrutura de comando.
 * @param i   Índice do array de redirecionamentos.
 */
void	get_redirects_2(t_command *seg, int *i)
{
	char	*msg;

	if (seg->std.in != -1 && !seg->here_doc)
		close(seg->std.in);
	if (access(&seg->red[*i][1], F_OK))
	{
		seg->redirect_error = 1;
		msg = build_error_message(&seg->red[*i][1], 0);
		display_error(2, msg, false);
		free(msg);
		return ;
	}
	if (!seg->here_doc)
	{
		seg->std.in = open(&seg->red[*i][1], O_RDONLY);
		if (seg->std.in == -1)
		{
			seg->redirect_error = 1;
			msg = build_error_message(&seg->red[*i][1], 0);
			display_error(2, msg, false);
			free(msg);
			return ;
		}
	}
}

/**
 * Função responsável por configurar as redirecionamentos 
 * de saída de um comando.
 * 
 * @param seg Ponteiro para a estrutura do comando.
 * @param i Ponteiro para o índice atual do redirecionamento.
 */
void	get_redirects_3(t_command *seg, int *i)
{
	char	*msg;

	if (seg->std.out != -1)
		close(seg->std.out);
	// if(seg->red[*i][0] == '>' && seg->red[*i][1] == '>' && seg->red[*i][2] == '\0')
	// 	printf("ola");
	if (seg->red[*i][0] == '>' && seg->red[*i][1] == '>')
	{
		seg->std.out = open(&seg->red[*i][2], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (seg->std.out == -1)
		{
			msg = build_error_message(&seg->red[*i][2], 0);
			display_error(1, msg, false);
			seg->redirect_error = 1;
			free(msg);
			return ;
		}
	}
	else if (seg->red[*i][0] == '>' && seg->red[*i][1] != '>')
	{
		seg->std.out = open(&seg->red[*i][1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (seg->std.out == -1)
		{
			msg = build_error_message(&seg->red[*i][1], 0);
			display_error(1, msg, false);
			seg->redirect_error = 1;
			free(msg);
			return ;
		}
	}
}
