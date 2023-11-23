/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:00:21 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 14:15:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Checks if the file descriptors in the given list are invalid and sets 
 * the appropriate error flags.
 * 
 * This function checks if the file descriptors in the given list are invalid. 
 * If any of the file descriptors in the `lst` parameter has a value of -1, 
 * it prints an error message using `perror()` and sets the corresponding
 * error flag in the `lst` structure. 
 * Additionally, it sets the global status variable `g_var.status` to 1.
 * 
 * @param lst The list containing the file descriptors to be checked.
 */
void invalid_fd(t_commands *lst)
{
	if (lst->fd_master[0] == -1)
	{
		perror("");
		g_var.exit_status = 1;
		lst->fd_master_error[0] = 1;
	}
	if (lst->fd_master[1] == -1)
	{
		perror("");
		g_var.exit_status = 1;
		lst->fd_master_error[1] = 1;
	}
}

/**
 * Check the type of token based on the given string.
 * 
 * @param str The string representing the token.
 * @return The type of token:
 *         1 for "<<",
 *         2 for ">>",
 *         3 for "<",
 *         4 for ">",
 *         0 for any other string.
 */
int check_redirection(char *str)
{
	if (!ft_strcmp(str, "<<"))
		return (1);
	else if (!ft_strcmp(str, ">>"))
		return (2);
	else if (!ft_strcmp(str, "<"))
		return (3);
	else if (!ft_strcmp(str, ">"))
		return (4);
	return (0);
}

/**
 * @brief Redirects input/output based on the given division and option.
 * 
 * @param division The array of strings representing the command division.
 * @param i The index of the current division being processed.
 * @param lst The list containing file descriptors and other information.
 */
void redirect(char **division, int *i, t_commands *lst)
{
	int option;

	option = check_redirection(division[*i]);
	if ((lst->fd_master[0] != -1 && lst->fd_master[1] != -1) || option == 1)
	{
		if (lst->fd_master[0] > 2 && (option == 1 || option == 3))
			close(lst->fd_master[0]);
		if (lst->fd_master[1] > 2 && (option == 2 || option == 4))
			close(lst->fd_master[1]);
		if (option == 2)
			lst->fd_master[1] = open(division[++(*i)], O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (option == 1)
			lst->fd_master[0] = here_doc(division[++(*i)]);
		else if (option == 3)
			lst->fd_master[0] = open(division[++(*i)], O_RDONLY, 0644);
		else if (option == 4)
			lst->fd_master[1] = open(division[++(*i)], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		invalid_fd(lst);
	}
}

/**
 * @brief Handles redirection in the given list of tokens.
 * 
 * This function iterates through the array of tokens and performs redirection
 * operations based on the tokens encountered. It supports input/output redirection,
 * appending output to a file, and redirecting input/output to/from a file.
 * 
 * @param lst The list of tokens.
 * @param division The array of tokens.
 */
void	tokens_redirection(t_commands *lst, char **division)
{
	int		i;
	int		j;
	t_commands	*temp;

	i = -1;
	j = 0;
	temp = lst;
	delete_quotes(division);
	while (division && division[++i])
	{
		if (division[i][0] == 3)
		{
			lst_add_back(&lst, lst_new(strlen_array(&division[i + 1])));
			if (temp->next)
				temp = temp->next;
			j = 0;
		}
		else if (check_redirection(division[i]))
			redirect(division, &i, temp);
		else
			temp->content[j++] = ft_strdup(division[i]);
	}
}