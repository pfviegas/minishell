/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:11:45 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/28 16:30:05 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Executa um comando interno com base no array de argumentos fornecido.
 *
 * @param cmd O array de argumentos do comando.
 * @param seg_error Um indicador de erro de segmentação.
 */
void execute_built_in(char **cmd, int seg_error)
{
	if (seg_error == 1)
	{
		shell()->exit_code = 1;
		return;
	}
	if (ft_strcmp(cmd[0], "cd") == 0)
		execute_cd(cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		execute_echo(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		execute_env(shell()->env);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(cmd[0], "unset")  == 0)
		execute_unset(cmd);
	else if (ft_strcmp(cmd[0], "export") == 0)
		execute_export(cmd);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		execute_exit(cmd);
}

/**
 * Função responsável por executar um comando built-in individualmente.
 * 
 * @param seg O comando a ser executado.
 */
void execute_single_built_in(t_command *seg)
{
	int in;
	int out;

	in = -1;
	out = -1;

	// Verifica se ocorreu um erro de redirecionamento
	if (seg->red_error == 1)
	{
		display_error(1, NULL, true);
		return;
	}

	// Redireciona a entrada padrão, se necessário
	if (seg->std.in != -1)
	{
		in = dup(STDIN_FILENO);
		dup2(seg->std.in, STDIN_FILENO);
		close(seg->std.in);
	}

	// Redireciona a saída padrão, se necessário
	if (seg->std.out != -1)
	{
		out = dup(STDOUT_FILENO);
		dup2(seg->std.out, STDOUT_FILENO);
		close(seg->std.out);
	}

	// Executa o comando built-in
	execute_built_in(seg->cmd, seg->red_error);

	// Restaura a entrada padrão, se necessário
	if (in != -1)
	{
		dup2(in, STDIN_FILENO);
		close(in);
	}

	// Restaura a saída padrão, se necessário
	if (out != -1)
	{
		dup2(out, STDOUT_FILENO);
		close(out);
	}
}

/**
 * Verifica se uma string representa um comando interno.
 *
 * @param str  A string a ser verificada.
 * @return     1 se a string representa um comando interno, 0 caso contrário.
 */
int is_built_in(char *str)
{
	if (ft_strcmp(str, "export") == 0 || ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0 || ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}
