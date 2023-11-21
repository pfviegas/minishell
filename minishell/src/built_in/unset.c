/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:20:44 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/09 16:37:52 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	both_prev_next(t_env **lst)
{
	(*lst)->prev->next = (*lst)->next;
	(*lst)->next->prev = (*lst)->prev;
	*lst = (*lst)->prev;
}

void	env_delete_element(t_env **lst)
{
	t_env	*temp;

	temp = (*lst);
	if (lst && *lst)
	{
		if (!(*lst)->prev && !(*lst)->next)
			*lst = NULL;
		else if (!(*lst)->prev && (*lst)->next)
		{
			(*lst)->next->prev = NULL;
			*lst = (*lst)->next;
		}
		else if ((*lst)->prev && !(*lst)->next)
		{
			(*lst)->prev->next = NULL;
			*lst = (*lst)->prev;
		}
		else if ((*lst)->prev && (*lst)->next)
			both_prev_next(lst);
		if (temp->data)
			free(temp->data);
		free(temp);
	}
}
// PFV
// falta testar
void	execute_unset(t_commands **command)
{
	t_env	*command_env_export;
	int		i;

	i = 1;
	if (!(*command)->content[1])
		return ;
	while ((*command)->content[i])
	{
		command_env_export = env_search((*command)->content[i]);
		if (command_env_export)
			env_delete_element(&command_env_export);
		i++;
	}
	g_data.exit_status = 0;
}