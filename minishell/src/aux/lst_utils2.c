/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:20:37 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/22 15:21:58 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Moves the given linked list to the first node.
 *
 * @param lst A pointer to the linked list.
 */
void lst_first(t_commands **lst)
{
	while ((lst) && (*lst) && (*lst)->prev)
		(*lst) = (*lst)->prev;
}

/**
 * Creates a new t_commands structure with the specified size and their pipe.
 * 
 * @param i The size of the content array.
 * @return A pointer to the newly created t_commands structure, 
 * or NULL if memory allocation fails.
 */
t_commands *lst_new(int i)
{
	t_commands *new;

	new = (t_commands *)ft_calloc(sizeof(t_commands), 1);
	if (!new)
		return (NULL);
	new->content = ft_calloc(sizeof(char *), i + 1);
	new->fd_master[0] = 0;
	new->fd_master[1] = 1;
	new->fd_master_error[0] = 0;
	new->fd_master_error[0] = 0;
	if (pipe(new->fd) == -1)
		perror("");
	return (new);
}