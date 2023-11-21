/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:22:04 by pveiga-c          #+#    #+#             */
/*   Updated: 2023/11/14 15:31:36 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_lst(t_listm *list)
{
	if (!list)
		return ;
	while (list)
	{
		printf("pipe line = %d\n", list->pipe_line);
		printf("id = %d\n", list->id);
		printf("content = %s\n", list->content);
		printf("cmd = %s\n", list->cmd);
		printf("in redir = %s\n", list->in_redir);
		printf("out redir = %s\n\n", list->out_redir);
		list = list->next;
	}
}

t_listm *update_list(t_prompt *parse, char **token)
{
	int i;
	t_listm *list;

	i = 0;
	list = NULL;
	while(i < parse->n_tokens)
	{
		lst_add_back(parse, &list, token[i], i);
		i++;
	}
	return (list);
}
void	lst_add_back(t_prompt *parse, t_listm **lst, char *new, int i)
{
	t_listm *new_node;
	t_listm *current;;
	
	new_node = malloc(sizeof(t_listm));
	if(!new_node)
		exit (1);
	new_node->next = NULL;
	new_node->id = i + 1;
	new_node->pipe_line = i;
	new_node->content = new;
	new_node->prompt = parse;
	split_content(new_node, new_node->content);
	if(!*lst)
	{
		*lst = new_node;
		return ;
	}
	current = *lst;
	while(current->next)
		current = current->next;
	current->next = new_node;
}



char **start_list(t_prompt *parse, char *p_input)
{
	int i;
	int j;
	int n;
	char **token;

	i = 0;
	n = 0;
	token = start_memory_list(parse, p_input);
	while(i < parse->n_tokens)
	{
		j = 0;
		while (p_input[n] == ' ' || p_input[n] == '\t')
			n++;
		while(p_input[n] && p_input[n] != '|')
		{
			token[i][j] = p_input[n];
			j++;
			n++;
		}
		token[i][j] = '\0';
		i++;
		n++;
	}
	return (token);
}

char **start_memory_list(t_prompt *parse, char *p_input)
{
	int i;
	int j;
	int n;
	char **token;

	i = 0;
	n = 0;
	token = malloc(sizeof(char **) * parse->n_tokens);
	while(i < parse->n_tokens)
	{
		j = 0;
		while(p_input[n] && p_input[n] != '|')
		{
			j++;
			n++;
		}
		token[i] = malloc(sizeof(char *) * j + 1);
		i++;
		n++;
	}
	return (token);
}