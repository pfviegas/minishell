/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pviegas <pviegas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:55:11 by pviegas           #+#    #+#             */
/*   Updated: 2023/12/01 17:14:52 by pviegas          ###   ########.fr       */
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
//		exibe uma mensagem de erro no stderr
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
//	enquanto a prompt estiver ativa
	while (shell()->prompt)
	{
//		exibe a prompt e captura o comando
		prompt_line = readline("minishell$ ");
//		se o comando for nulo ou vazio, sai do minishell
		if (!prompt_line)
		{
//			mensagem de saida CTRL+D
			printf("exit\n");
//			libera a memoria alocada
			free_all(true, false, true, false);
//			sai do minishell com o codigo de saida 0
			exit(0);
		}
		if (prompt_line[0] != '\n' || prompt_line[0] != '\0')
		{
// 			adiciona o comando ao historico
			add_history(prompt_line);
// 			verifica se o comando é valido
			parsing(prompt_line);
// 			se o comando for valido, executa
			if (!shell()->error)
//				executa o comando
				executor(shell()->tokens_lst);
//			libera a memoria alocada
 			free_all(false, true, false, false);
		}
	}
//	exibe uma nova linha
//		printf("\n");
//	libera a memoria alocada
	free_all(true, false, true, false);
//	limpa o historico do readline
	rl_clear_history();
//	retorna o codigo de saida do minishell
	return (shell()->exit_code);
}
