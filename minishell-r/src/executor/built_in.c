/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:11:45 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/28 13:13:07 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * Executa um comando interno com base no array de argumentos fornecido.
 *
 * @param cmd O array de argumentos do comando.
 * @param seg_error Um indicador de erro de segmentação.
 */
void	execute_built_in(char **cmd, int seg_error)
{
	if (seg_error == 1)
	{
		shell()->exit_code = 1;
		return ;
	}
	if (ft_strcmp(cmd[0], "cd") == 0)
		execute_cd(cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		execute_echo(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		execute_env(shell()->env);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(cmd[0], "unset") == 0)
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
void	execute_single_built_in(t_command *token)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = -1;
	saved_stdout = -1;
	if (token->redirect_error == 1)
	{
		return ;
	}
	redirect_standard_input(token, &saved_stdin);
	redirect_standard_output(token, &saved_stdout);
	execute_built_in(token->cmd, token->redirect_error);
	restore_standard_input(saved_stdin);
	restore_standard_output(saved_stdout);
}

/**
 * Verifica se uma string representa um comando interno.
 *
 * @param str  A string a ser verificada.
 * @return     1 se a string representa um comando interno, 0 caso contrário.
 */
int	is_built_in(char *str)
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
