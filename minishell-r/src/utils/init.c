/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:47:43 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/21 16:05:37 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Inicializa as variáveis da shell.
 *
 * Esta função atribui valores iniciais às variáveis da estrutura t_shell e
 * obtém as variáveis de ambiente.
 *
 * @param shell A estrutura t_shell que contém as variáveis da shell.
 * @param envp  O array de strings contendo as variáveis de ambiente.
 */
void	init_shell_vars(t_shell *shell, char **envp)
{
	shell->error = false;
	shell->segments_lst = NULL;
	shell->env = get_env_vars(envp);
	shell->exit_code = 0;
	shell->in_here_doc = false;
	shell->in_exec = false;
	shell->rep_prompt = NULL;
}

/**
 * Inicializa a estrutura t_command com valores padrão.
 *
 * Esta função atribui valores iniciais aos membros da estrutura t_command.
 *
 * @param seg Ponteiro para a estrutura t_command a ser inicializada.
 */
void	init_command(t_command *token)
{
	token->here_doc = false;
	token->redirect_error = 0;
	token->cmd = NULL;
	token->red = NULL;
	token->here = NULL;
	token->std.in = -1;
	token->std.out = -1;
}

/**
 * Inicializa as flags de comandos built in.
 * 
 * Esta função percorre a lista de segmentos de comandos e verifica se cada
 * comando é um comando interno. Caso seja, a flag `built_in` do segmento é
 * definida como verdadeira.
 * 
 * @param lst A lista de segmentos de comandos.
 */
void	init_built_in_flags(t_list *lst)
{
	t_list		*temp;
	t_command	*tokens;
	int			i;

	temp = lst;
	while (temp)
	{
		tokens = (t_command *)temp->content;
		tokens->built_in = false;
		i = -1;
		while (tokens->cmd && tokens->cmd[++i])
		{
			if (is_built_in(tokens->cmd[i]))
				tokens->built_in = true;
		}
		temp = temp->next;
	}
}
