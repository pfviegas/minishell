/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:40:41 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/22 17:12:08 by pviegas          ###   ########.fr       */
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
	char		*msg;

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
		if (seg->redirect_error == 1)
		{
			msg = "minishell: syntax error near unexpected token `newline'";
			display_error(2, msg, false);
		}
		temp = temp->next;
	}
}

void	get_redirects_2(t_command *seg, int *i)
{
	if (seg->std.in != -1 && !seg->here_doc)
		close(seg->std.in);
	if (access(&seg->red[*i][1], F_OK))
	{
		seg->redirect_error = 1;
		return ;
	}
	if (!seg->here_doc)
	{
		seg->std.in = open(&seg->red[*i][1], O_RDONLY);
		if (seg->std.in == -1)
		{
			seg->redirect_error = 1;
			return ;
		}
	}
}

void	get_redirects_3(t_command *seg, int *i)
{
	if (seg->std.out != -1)
		close(seg->std.out);
	if (seg->red[*i][0] == '>' && seg->red[*i][1] == '>')
	{
		seg->std.out = open(&seg->red[*i][2], \
		O_RDWR | O_CREAT | O_APPEND, 0644);
		if (seg->std.out == -1)
		{
			seg->redirect_error = 1;
			return ;
		}
	}
	else if (seg->red[*i][0] == '>' && seg->red[*i][1] != '>')
	{
		seg->std.out = open(&seg->red[*i][1], \
		O_RDWR | O_CREAT | O_TRUNC, 0644);
		if (seg->std.out == -1)
		{
			seg->redirect_error = 1;
			return ;
		}
	}
}
