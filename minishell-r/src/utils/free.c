/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 16:10:10 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/09 16:43:48 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Libera a memória alocada para um array de strings.
 *
 * @param array O ponteiro para o array de strings.
 */
void	free_array(char ***array)
{
	int	i;
	int	len;

	if (!(*array))
		return ;
	len = 0;
	while ((*array)[len])
		len++;
	i = -1;
	while (++i < len)
		free((*array)[i]);
	free((*array));
}

/**
 * Libera a memória alocada pelo shell.
 *
 * Esta função libera a memória alocada pelo shell, 
 * de acordo com as opções fornecidas.
 *
 * @param free_env       Indica se a memória do ambiente deve ser liberada.
 * @param free_cmd_lst   Indica se a memória da lista de comandos 
 *                       deve ser liberada.
 * @param std_files      Indica se os arquivos de entrada e saída padrão 
 *                       devem ser fechados.
 * @param f_exit         Indica se o shell deve ser encerrado.
 */
void	free_all(bool free_env, bool free_cmd_lst, bool std_files, bool f_exit)
{
	shell()->error = false;
	if (free_env == true)
		free_array(&shell()->env);
	if (free_cmd_lst == true)
	{
		if (shell()->segments_lst)
			free_lst(shell()->segments_lst);
	}
	if (std_files == true)
	{
		close(2);
		close(1);
		close(0);
	}
	if (f_exit == true)
		exit(shell()->exit_code);
}

/**
 * Libera a memória alocada para uma lista encadeada.
 * 
 * @param temp Ponteiro para o primeiro elemento da lista.
 */
void	free_lst(t_list *lst)
{
	t_list		*next;
	t_command	*seg;

	while (lst)
	{
		next = lst->next;
		seg = (t_command *)lst->content;
		if (seg && seg->cmd)
			free_array(&seg->cmd);
		if (seg && seg->red)
			free_array(&seg->red);
		if (seg && seg->in)
			free_array(&seg->in);
		if (seg && seg->out)
			free_array(&seg->out);
		if (seg && seg->here)
			free_array(&seg->here);
		if (seg && seg->std.in != -1)
			close(seg->std.in);
		if (seg && seg->std.out != -1)
			close(seg->std.out);
		free(seg);
		free(lst);
		lst = next;
	}
}
