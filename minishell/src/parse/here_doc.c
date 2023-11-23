/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:21:06 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 14:15:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Function to handle here-document errors.
 * 
 * @param str The string that caused the error.
 * @return Returns 1 to indicate an error occurred.
 */
int here_doc_error(char *str)
{
	write(2, "warning: here-document at line 1 \
	delimited by end-of-file (wanted `", 67);
	write(2, str, ft_strlen(str));
	write(2, "')\n", 3);
	return (1);
}

/**
 * Is responsible for handling the child process in the here document feature.
 * It reads input from the user until a specific string is entered, 
 * and writes the input to a file descriptor.
 * Also performs environment variable substitution on the input string.
 *
 * @param str The specific string that indicates the end of the here document.
 * @param fd The file descriptor used for writing the input.
 */
void	here_doc_child(char *str, int *fd)
{
//PFV
//	term_change();
	g_var.vars->env = lst_to_arr(g_var.env);
	while (1)
	{
		write(0, ">", 1);
		g_var.vars->str = ft_get_next_line(0);
		g_var.vars->str = chg_dollar(g_var.vars->str, g_var.vars->env);
		if (!g_var.vars->str && here_doc_error(str))
			break ;
		if ((ft_strncmp(g_var.vars->str, str, ft_strlen(str)) == 0) && \
			(ft_strlen(g_var.vars->str) - 1 == ft_strlen(str)))
			break ;
		write(fd[1], g_var.vars->str, ft_strlen(g_var.vars->str));
		free(g_var.vars->str);
		g_var.vars->str = NULL;
	}
	free_env(&g_var.env);
	free_vars();
	close(fd[1]);
	close(fd[0]);
	exit(0);
}

/**
 * Executes the here_doc command.
 * 
 * @param str The string to be used as input for the here_doc command.
 * @return The file descriptor for reading the output of the here_doc command.
 */
int here_doc(char *str)
{
	int fd[2];
	int status;

	status = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, here_doc_signals);
	g_var.here_doc = 1;
	if (pipe(fd) == -1)
		perror("");
	if (fork() == 0)
		here_doc_child(str, fd);
	signals_behavior();
	close(fd[1]);
	waitpid(0, &status, 0);
	g_var.here_doc = 0;
	return (fd[0]);
}