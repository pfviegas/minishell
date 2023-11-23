/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:54:49 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/23 14:32:43 by pviegas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Lida com o sinal de interrupção (SIGINT) imprimindo uma mensagem 
 * e atualizando o status de saída.
 * 
 * @param sign O número do sinal.
 */
void handle_sign(int sign)
{
	pid_t pid;
	int status;

	pid = waitpid(-1, &status, 0);
	g_var.exit_status = 130;
	(void)sign;
	write(2, "^C", 2);
	write(2, "\n", 1);
	if (g_var.here_doc)
	{
		g_var.interrupted = 1;
		return ;
	}
	if (pid == -1)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * @brief Lida com o sinal de quit SIGQUIT.
 * 
 * Esta função é chamada quando o sinal de quit é recebido. 
 * Ela espera que qualquer processo filho termine e imprime uma mensagem 
 * indicando que o processo terminou com um core dump. 
 * Se a flag here_doc não estiver definida, ela imprime a 
 * mensagem "Quit (core dumped)" na saída padrão.
 * 
 * @param sign O número do sinal.
 */
void	handle_quit(int sign)
{
	pid_t	pid;
	int		status;

	(void)sign;
	pid = waitpid(-1, &status, 0);
	if (pid == -1)
		SIG_IGN ;
	else if (!g_var.here_doc)
	{
		write(1, "Quit (core dumped)\n", 20);
		return ;
	}
}

/**
 * Configura o comportamento dos sinais SIGINT e SIGQUIT.
 */
void signals_behavior(void)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, handle_quit);
}

/**
 * @brief Lida com os sinais para here documents.
 * 
 * Esta função é responsável por lidar com os sinais relacionados aos here documents.
 * Ela ignora o sinal SIGQUIT e realiza operações de limpeza e sai quando recebe o sinal SIGINT.
 * 
 * @param sign O número do sinal.
 */
void here_doc_signals(int sign)
{
	if (sign == SIGQUIT)
		SIG_IGN;
	else if (sign == SIGINT)
	{
		write(2, " ", 1);
		free_env(&g_var.env);
		free_vars();
		exit(1);
	}
}
