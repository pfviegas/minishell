/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:57:06 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/05 13:24:19 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Redireciona a entrada padrão para o descritor de arquivo especificado 
 * em `token`.
 * 
 * @param token        O comando que contém as informações de redirecionamento.
 * @param saved_stdin  Um ponteiro para a variável que armazenará 
 *                     o descritor de arquivo da entrada padrão original.
 */
void redirect_standard_input(t_command *token, int *saved_stdin)
{
	if (token->std.in != -1)
	{
		*saved_stdin = dup(STDIN_FILENO);
		dup2(token->std.in, STDIN_FILENO);
		close(token->std.in);
	}
}


/**
 * Redireciona a saída padrão para o arquivo especificado em `token->std.out`.
 * Salva o descritor de arquivo da saída padrão original em `saved_stdout`.
 *
 * @param token        O comando que contém as informações de redirecionamento
 * @param saved_stdout O ponteiro para a variável que armazenará 
 *                     o descritor de arquivo da saída padrão original.
 */
void redirect_standard_output(t_command *token, int *saved_stdout)
{
	if (token->std.out != -1)
	{
		*saved_stdout = dup(STDOUT_FILENO);
		dup2(token->std.out, STDOUT_FILENO);
		close(token->std.out);
	}
}

/**
 * Restaura a entrada padrão do programa.
 *
 * Restaura a entrada padrão do programa para o descritor de arquivo
 * especificado por `saved_stdin`. Se `saved_stdin` for diferente de -1,
 * a função utiliza a função `dup2` para redirecionar a entrada padrão 
 * para o descritor de arquivo `saved_stdin` e em seguida 
 * fecha o descritor de arquivo `saved_stdin`.
 *
 * @param saved_stdin O descritor de arquivo da entrada padrão salvo anteriormente.
 */
void	restore_standard_input(int saved_stdin)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
}


/**
 * Restaura a saída padrão.
 *
 * Esta função restaura a saída padrão do programa, caso tenha sido 
 * redirecionada anteriormente. Ela recebe como parâmetro o descritor 
 * de arquivo salvo da saída padrão e utiliza a função `dup2` para 
 * redirecionar a saída de volta para o descritor de arquivo original. 
 * Em seguida, o descritor de arquivo salvo é fechado.
 *
 * @param saved_stdout O descritor de arquivo salvo da saída padrão.
 */
void	restore_standard_output(int saved_stdout)
{
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}
