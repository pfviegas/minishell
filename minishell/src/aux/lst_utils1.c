/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 16:05:40 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/07 14:08:14 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Mostra o conteudo da lista com os comandos apos o parser
void	print_lst(t_commands *command)
{
	int	i;

	if (!command)
		return ;
	while (command)
	{
		i = -1;
		printf("\nendereco: %p\n", command);
		printf("content: ");
		while (command->content[++i])
			printf("%s ", command->content[i]);
		printf("\nfd in: %i\n", command->fd[0]);
		printf("fd out: %i\n", command->fd[1]);
		printf("fd OW in: %i\n", command->fd_master[0]);
		printf("fd OW out: %i\n\n", command->fd_master[1]);
		command = command->next;
	}
}

// Converte uma lista numa variavel do tipo char**
char	**lst_to_arr(t_env *lst_env)
{
	int		size;
	char	**arr;
	int		i;

	size = env_lst_size(lst_env);
	arr = (char **)malloc((size + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	env_first(&lst_env);
	while (lst_env)
	{
		arr[i] = lst_env->data;
		lst_env = lst_env->next;
		i++;
	}
	arr[size] = NULL;
	return (arr);
}

//Retorna o ultimo elemento de uma linked list
t_commands	*lst_last(t_commands *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

//Acrescenta um elemento no final da linked list
//Ou seja, coloca o last->next a apontar para o new
void	lst_add_back(t_commands **lst, t_commands *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = lst_last(*lst);
			lst_last(*lst)->next = new;
		}
		else
		{
			*lst = new;
		}
	}
}

int	lst_size(t_commands *lst)
{
	int			count;
	t_commands	*node;

	count = 0;
	node = lst;
	while (node != NULL)
	{
		count++;
		node = node->next;
	}
	return (count);
}

