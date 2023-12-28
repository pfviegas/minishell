/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:18:18 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/12/28 12:13:49 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_here_doc(t_list *lst)
{
	t_list		*temp;
	t_command	*token;
	int			i;

	temp = lst;
	while (temp)
	{
		token = (t_command *)temp->content;
		i = -1;
		while (token->red && token->red[++i])
			here_doc_red(i, token);
		if (token->here && token->here_doc)
		{
			token->std.in = here_doc(token);
			if (token->std.in == -1)
				return (1);
		}
		else if (token->here)
		{
			if (close(here_doc(token)) == -1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	here_doc_red(int i, t_command *token)
{
	if (token->red[i][0] == '<' && token->red[i][1] == '<')
	{
		add_str_to_array(&token->here, &token->red[i][2]);
		token->here_doc = true;
	}
	else if (token->red[i][0] == '<')
		token->here_doc = false;
}

void	print_matriz(char **matriz)
{
	int		i;

	i = 0;
	printf("---------------matriz-------------\n\n");
	while (matriz[i])
	{
		printf("%s\n", matriz[i]);
		i++;
	}
}
