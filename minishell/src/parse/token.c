/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:23:15 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/11/14 15:26:05 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void count_tokens(t_prompt *parse, char *p_input)
{
	size_t i;

	i = -1;
	while(++i < ft_strlen(p_input))
	{
		if(p_input[i] == '|')
			parse->n_pipes++;
	}
	parse->n_tokens = parse->n_pipes + 1;
	//printf("pipes = %d\n", parse->n_pipes);
	//printf("tokens = %d\n", parse->n_tokens);
}
void split_content(t_listm *node, char *content)
{
	int i;
	int op;
	int j;

	i = 0;
	op = 0;
	while(content[i] && (content[i] != '<' && content[i] != '>'))
			i++;
	if( content[i] == '>')
		op = 1;
	node->cmd = malloc(sizeof(char *) * i + 1);
	if(!node->cmd)
		perror("Malloc Error\n");
	while(content[i])
		i++;
	if(op == 0)
		node->in_redir = malloc(sizeof(char *) * i + 1);
	else
		node->out_redir = malloc(sizeof(char *) * i + 1);
	if(!node->in_redir && !node->out_redir)
		perror("Malloc Error\n");
	i = 0;
	while(content[i] != '<' && content[i] != '>')
	{
		node->cmd[i] = content[i];
		i++;	
	}
	node->cmd[i] = '\0';
	j = -1;
	if(op == 0)
	{
		while(content[++i])
			node->in_redir[++j] = content[i];
		node->in_redir[j] = '\0';
	}
	if(op == 1)
	{
		while(content[++i])
			node->out_redir[++j]= content[i];
		node->out_redir[j] = '\0';
	}
	// printf("pipe_line = %d\n", node->pipe_line);
	// printf("content = %s\n", content);
	// printf("cmd = %s\n", node->cmd);
	// printf("in = %s\n", node->in_redir);
	// printf("out = %s\n\n", node->out_redir);
}