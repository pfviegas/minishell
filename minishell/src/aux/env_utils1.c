/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:08:25 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 14:11:47 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Retorna o último nó da lista encadeada de variáveis de ambiente.
 *
 * @param lst O ponteiro para o primeiro nó da lista.
 * @return O ponteiro para o último nó da lista.
 */
t_env *env_last(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/**
 * Adiciona um novo elemento no fim da lista encadeada de variáveis de ambiente
 *
 * @param lst Ponteiro para o ponteiro da lista encadeada.
 * @param new O novo elemento a ser adicionado.
 */
void env_add_back(t_env **lst, t_env *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = env_last(*lst);
			env_last(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

/**
 * Cria uma nova variável de ambiente com a string fornecida.
 *
 * @param str A string que representa a variável de ambiente.
 * @return Um ponteiro para a nova variável de ambiente criada.
 */
t_env *env_new(char *str)
{
	t_env *new;

	new = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new)
		return (NULL);
	new->data = str;
	return (new);
}

/* Retorna o primeiro elemento */
void	env_first(t_env **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}
