/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:54:49 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/26 17:46:00 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/**
 * @brief Lida com o sinal de interrupção (SIGINT) imprimindo 
 * uma mensagem e atualizando o status de saída.
 * 
 * @param signal O número do sinal.
 */
void	handle_sign(int signal)
{
	(void)signal;
	shell()->exit_code = 130;
	if (shell()->in_exec == true)
		return ;
	if (shell()->in_here_doc == false)
	{
		printf("^C\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
	{
		display_error(130, "", true);
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
void	handle_quit(int signal)
{
	(void)signal;
	if (shell()->in_exec == true)
	{
		shell()->exit_code = 131;
		ft_putstr_fd("Quit (core dumped)\n", 2);
	}
}

/**
 * Configura o comportamento dos sinais SIGINT e SIGQUIT.
 */
void	signals_behavior(void)
{
	signal(SIGINT, handle_sign);
	signal(SIGQUIT, handle_quit);
}
