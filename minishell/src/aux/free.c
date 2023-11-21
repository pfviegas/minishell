/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 16:29:07 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/20 12:21:50 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// Liberta a memoria de uma variavel do tipo char** 
void	free_str_array(char ***str_array)
{
	int	i;

	i = 0;
	while (str_array && str_array[0] && str_array[0][i])
	{
		free(str_array[0][i]);
		i++;
	}
	if (str_array)
	{
		free(str_array[0]);
		*str_array = NULL;
	}
}

int	free_vars(void)
{
	if (g_data.vars)
	{
		if (g_data.vars->head)
		{
			lst_first(&g_data.vars->head);
			free_list(&g_data.vars->head);
		}
		if (g_data.vars->str)
			free(g_data.vars->str);
		if (g_data.vars->env)
			free_str_array(&g_data.vars->env);
		if (g_data.vars->division)
			free_str_array(&g_data.vars->division);
		free(g_data.vars);
	}
	return (1);
}

// Liberta a memoria da linked list que guarda os comandos a executar
void	free_list(t_commands **lst)
{
	t_commands	*aux;

	while (*lst)
	{
		aux = (*lst)->next;
		close((*lst)->fd[0]);
		close((*lst)->fd[1]);
		free_str_array(&(*lst)->content);
		free((*lst)->path);
		free((*lst)->content);
		free(*lst);
		*lst = aux;
	}
	g_data.vars->head = NULL;
}

// Liberta a memoria da linked list que guarda as variaveis de ambiente
int	free_env(t_env **lst)
{
	t_env	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
//		free((*lst)->data);
		free(*lst);
		*lst = temp;
	}
	return (1);
}
