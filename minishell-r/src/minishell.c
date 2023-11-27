/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pveiga-c <pveiga-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:55:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/11/27 17:33:00 by pveiga-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Estrutura Principal
/**
 * @brief Retorna um ponteiro para a estrutura t_shell.
 * 
 * Esta função retorna um ponteiro para a estrutura t_shell, 
 * que é uma estrutura utilizada para armazenar informações do Minishell.
 * 
 * @return Um ponteiro para a estrutura t_shell.
 */
t_shell	*shell(void)
{
	static t_shell	shell;

	return (&shell);
}
int	main(int argc, char **argv, char **envp)
{
	char	*prompt_line;

//	verifica se o numero de argumentos é valido	
	if (argc != 1)
	{
		write(2, "minishell: ", 11);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, ": No such file or directory\n", 28);
		return (127);
	}
//	limpa o historico do readline
	rl_clear_history();
//	desativa a captura de sinais pelo readline 
	rl_catch_signals = 0;
//	define o comportamento dos sinais
	signals_behavior();
//	inicializa o estado da prompt	
	shell()->prompt = true;
//	inicializa as variaveis de ambiente	
	init_shell_vars(shell(), envp);
	while (shell()->prompt)
	{
		prompt_line = readline("minishell$ ");
		if (!prompt_line)
		{
			free_all(true, false, true, false);
			exit(0);
		}
		if (prompt_line[0] != '\n' || prompt_line[0] != '\0')
		{
// 			adiciona o comando ao historico
			add_history(prompt_line);
// 			verifica se o comando é valido
			parsing(prompt_line);
//			if (!shell()->error)
//				run(shell()->segment_lst);
 			free_all(false, true, false, false);		
		}
	}
	free_all(true, false, true, false);
	printf("\n");
	return (shell()->exit_code);
}
